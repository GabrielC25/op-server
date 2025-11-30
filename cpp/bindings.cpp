#include "bindings.hpp"
#include "Server.hpp"
#include "macros.hpp"
#include <string>
#include <unordered_map>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
namespace opserver {

namespace jsi = facebook::jsi;
namespace react = facebook::react;

std::vector<std::shared_ptr<Server>> servers;

// React native will try to clean the module on JS context invalidation
// (CodePush/Hot Reload) The clearState function is called
void invalidate() {
  for (auto &server : servers) {
    if (server) {
      server->stop();
    }
  }
  servers.clear();
}

void install(jsi::Runtime &rt,
             const std::shared_ptr<react::CallInvoker> &invoker) {

  const auto create = HFN(invoker) {
    std::shared_ptr<Server> server = std::make_shared<Server>(rt, invoker);
    servers.emplace_back(server);
    return jsi::Object::createFromHostObject(rt, server);
  });

  jsi::Object module = jsi::Object(rt);
  module.setProperty(rt, "create", create);

  rt.global().setProperty(rt, "__OPServerProxy", std::move(module));
}

} // namespace opserver

#pragma clang diagnostic pop
