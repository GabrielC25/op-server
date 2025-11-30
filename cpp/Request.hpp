#pragma once

#include <httplib.h>
#include <jsi/jsi.h>
#include <string>
#include <unordered_map>

namespace opserver {

namespace jsi = facebook::jsi;

class JSI_EXPORT Request : public jsi::HostObject {
public:
  explicit Request(const httplib::Request &req);

  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
  jsi::Value get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) override;

private:
  std::string method;
  std::string path;
  std::string body;
  std::unordered_map<std::string, std::string> headers;
  std::unordered_map<std::string, std::string> params;
};

} // namespace opserver
