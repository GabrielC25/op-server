#pragma once

#include <ReactCommon/CallInvoker.h>
#include <jsi/jsi.h>

#include <httplib.h>

namespace opserver {

namespace jsi = facebook::jsi;
namespace react = facebook::react;


class JSI_EXPORT Server : public jsi::HostObject {
public:
  Server(jsi::Runtime &rt, std::shared_ptr<react::CallInvoker> invoker);
  std::vector<jsi::PropNameID> getPropertyNames(jsi::Runtime &rt) override;
  jsi::Value get(jsi::Runtime &rt, const jsi::PropNameID &propNameID) override;
  void set(jsi::Runtime &rt, const jsi::PropNameID &name,
           const jsi::Value &value) override;
  void stop();
  ~Server() override;

private:
  httplib::Server server;
  std::unordered_map<std::string, jsi::Value> function_map;
};

} // namespace opserver
