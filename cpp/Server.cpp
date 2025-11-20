#pragma once

#include "Server.hpp"
#include "macros.hpp"
#include <future>
#include <iostream>

namespace opserver {

namespace jsi = facebook::jsi;
namespace react = facebook::react;

Server::Server(jsi::Runtime &rt, std::shared_ptr<react::CallInvoker> invoker) {

  function_map["callback"] = HFN2(this, invoker) {
    const std::string method = args[0].asString(rt).utf8(rt);
    const std::string path = args[1].asString(rt).utf8(rt);
    auto callback = std::make_shared<jsi::Value>(rt, args[2]);

    // Abstracted request handler
    auto handleRequest = [this, &rt, invoker,
                          callback](const httplib::Request &req,
                                    httplib::Response &res) {
      auto responseDone = std::make_shared<std::promise<std::string>>();
      auto responseFuture = responseDone->get_future();

      invoker->invokeAsync([callback, responseDone](jsi::Runtime &rt) {
        try {
          auto promise = callback->asObject(rt).asFunction(rt).call(rt);

          auto promiseObj = promise.asObject(rt);
          auto then_fn = promiseObj.getPropertyAsFunction(rt, "then");
          auto catch_fn = promiseObj.getPropertyAsFunction(rt, "catch");

          // Create success handler
          auto success_handler = HFN(responseDone) {
            if (count > 0 && args[0].isString()) {
              responseDone->set_value(args[0].asString(rt).utf8(rt));
            } else {
              responseDone->set_value("Success!");
            }
            return jsi::Value::undefined();
          });

          // reject handler
          auto reject_handler = HFN(responseDone) {
            std::string errorMsg = "Error: ";
            if (count > 0) {
              if (args[0].isString()) {
                errorMsg += args[0].asString(rt).utf8(rt);
              } else if (args[0].isObject()) {
                auto errObj = args[0].asObject(rt);
                if (errObj.hasProperty(rt, "message")) {
                  auto msgVal = errObj.getProperty(rt, "message");
                  if (msgVal.isString()) {
                    errorMsg += msgVal.asString(rt).utf8(rt);
                  }
                }
              }
            }
            responseDone->set_value(errorMsg);
            return jsi::Value::undefined();
          });

          then_fn.callWithThis(rt, promiseObj, success_handler);
          catch_fn.callWithThis(rt, promiseObj, reject_handler);

        } catch (const std::exception &e) {
          responseDone->set_value(std::string("Error: ") + e.what());
        }
      });

      if (responseFuture.wait_for(std::chrono::seconds(5)) ==
          std::future_status::ready) {
        res.set_content(responseFuture.get(), "text/plain");
      } else {
        res.set_content("Timeout", "text/plain");
      }
    };

    // Register the appropriate HTTP method
    if (method == "GET") {
      server.Get(path, handleRequest);
    } else if (method == "POST") {
      server.Post(path, handleRequest);
    } else if (method == "PUT") {
      server.Put(path, handleRequest);
    } else if (method == "DELETE") {
      server.Delete(path, handleRequest);
    }

    return {};
  });

  //  function_map["getIp"] = HFN(this) {
  //    std::string ip;
  //    int port;
  //    // Get the local IP and port from the server socket
  //    auto sock = server.socket();
  //    if (sock != -1) {
  //      detail::get_local_ip_and_port(sock, ip, port);
  //      return jsi::String::createFromUtf8(rt, ip);
  //    }
  //
  //    return jsi::Value::undefined();
  //  });

  function_map["listen"] = HFN(this) {
    std::thread([this]() { server.listen("0.0.0.0", 3000); }).detach();
    return {};
  });
}

std::vector<jsi::PropNameID> Server::getPropertyNames(jsi::Runtime &_rt) {
  std::vector<jsi::PropNameID> keys;
  keys.reserve(function_map.size());
  for (const auto &pair : function_map) {
    keys.emplace_back(jsi::PropNameID::forUtf8(_rt, pair.first));
  }
  return keys;
}

jsi::Value Server::get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) {
  const auto name = propNameID.utf8(rt);
  if (function_map.count(name) != 1) {
    return HFN(name) {
      throw std::runtime_error("[op-server] Function " + name +
                               " not implemented");
    });
  }

  return {rt, function_map[name]};
}

void Server::set(jsi::Runtime &_rt, const jsi::PropNameID &name,
                 const jsi::Value &value) {
  throw std::runtime_error("You cannot write to this object!");
}

void Server::stop() {
  //  http_server_
}

Server::~Server() {

};

} // namespace opserver
