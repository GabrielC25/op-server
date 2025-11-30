#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

#include "Response.hpp"
#include "macros.hpp"

namespace opserver {

Response::Response() {
  statusCode = 200;
  content = "";
  contentType = "text/plain";
}

std::vector<jsi::PropNameID> Response::getPropertyNames(jsi::Runtime &rt) {
  std::vector<jsi::PropNameID> keys;
  keys.push_back(jsi::PropNameID::forUtf8(rt, "statusCode"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "content"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "contentType"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "headers"));
  keys.push_back(jsi::PropNameID::forUtf8(rt, "setHeader"));
  return keys;
}

jsi::Value Response::get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) {
  const auto name = propNameID.utf8(rt);

  if (name == "statusCode") {
    return {statusCode};
  }

  if (name == "content") {
    return jsi::String::createFromUtf8(rt, content);
  }

  if (name == "contentType") {
    return jsi::String::createFromUtf8(rt, contentType);
  }

  if (name == "headers") {
    auto obj = jsi::Object(rt);
    for (const auto &header : headers) {
      obj.setProperty(rt, header.first.c_str(),
                      jsi::String::createFromUtf8(rt, header.second));
    }
    return obj;
  }

  if (name == "setHeader") {
    return HFN(this) {
      if (count < 2) {
        throw jsi::JSError(rt, "setHeader requires 2 arguments: key and value");
      }

      std::string key = args[0].asString(rt).utf8(rt);
      std::string value = args[1].asString(rt).utf8(rt);
      this->headers[key] = value;

      return jsi::Value::undefined();
    });
  }

  return jsi::Value::undefined();
}

void Response::set(jsi::Runtime &rt, const jsi::PropNameID &propNameID,
                   const jsi::Value &value) {
  const auto name = propNameID.utf8(rt);

  if (name == "statusCode") {
    if (value.isNumber()) {
      statusCode = static_cast<int>(value.asNumber());
    }
    return;
  }

  if (name == "content") {
    if (value.isString()) {
      content = value.asString(rt).utf8(rt);
    }
    return;
  }

  if (name == "contentType") {
    if (value.isString()) {
      contentType = value.asString(rt).utf8(rt);
    }
    return;
  }

  throw jsi::JSError(rt, "Property '" + name + "' is not settable");
}

void Response::applyTo(httplib::Response &res) {
  res.status = statusCode;
  res.set_content(content, contentType);

  for (const auto &header : headers) {
    res.set_header(header.first, header.second);
  }
}

} // namespace opserver

#pragma clang diagnostic pop
