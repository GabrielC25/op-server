#pragma once

#include <httplib.h>
#include <jsi/jsi.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace opserver {

namespace jsi = facebook::jsi;

class JSI_EXPORT Response : public jsi::HostObject {
public:
  Response();

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
  jsi::Value get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) override;
  void set(jsi::Runtime &rt, const jsi::PropNameID &name,
           const jsi::Value &value) override;

  // Apply the changes back to the httplib::Response
  void applyTo(httplib::Response &res);

private:
  int statusCode;
  std::string content;
  std::string contentType;
  std::unordered_map<std::string, std::string> headers;
};

} // namespace opserver
