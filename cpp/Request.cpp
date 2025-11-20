#include "Request.hpp"
#include "macros.hpp"

namespace opserver {

Request::Request(const httplib::Request &req) {
  method = req.method;
  path = req.path;
  body = req.body;

  // Copy headers
  for (const auto &header : req.headers) {
    headers[header.first] = header.second;
  }

  // Copy query params
  for (const auto &param : req.params) {
    params[param.first] = param.second;
  }
}

std::vector<jsi::PropNameID> Request::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> keys;
  keys.push_back(jsi::PropNameID::forUtf8(rt, "method"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "path"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "body"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "headers"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "params"));
  return keys;
}

jsi::Value Request::get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) {
  const auto name = propNameID.utf8(rt);

  if (name == "method") {
    return jsi::String::createFromUtf8(rt, method);
  }

  if (name == "path") {
    return jsi::String::createFromUtf8(rt, path);
  }

  if (name == "body") {
    return jsi::String::createFromUtf8(rt, body);
  }

  if (name == "headers") {
    auto obj = jsi::Object(rt);
    for (const auto &header : headers) {
      obj.setProperty(rt, header.first.c_str(),
                      jsi::String::createFromUtf8(rt, header.second));
    }
    return obj;
  }

  if (name == "params") {
    auto obj = jsi::Object(rt);
    for (const auto &param : params) {
      obj.setProperty(rt, param.first.c_str(),
                      jsi::String::createFromUtf8(rt, param.second));
    }
    return obj;
  }

  return jsi::Value::undefined();
}

void Request::set(jsi::Runtime &rt, const jsi::PropNameID &name,
                  const jsi::Value &value) {
  // Request is read-only from JS side
  throw jsi::JSError(rt, "Request object is read-only");
}

} // namespace opserver
