#import "OpServer.h"
#import "bindings.hpp"
#import <ReactCommon/CallInvoker.h>
#import <ReactCommon/RCTTurboModuleWithJSIBindings.h>


using namespace facebook;

@interface OpServer () <RCTTurboModuleWithJSIBindings>
@end

@implementation OpServer {
  bool _didInstall;
  std::weak_ptr<react::CallInvoker> _callInvoker;
}
RCT_EXPORT_MODULE(OpServer)

- (void)installJSIBindingsWithRuntime:(jsi::Runtime &)runtime callInvoker:(const std::shared_ptr<facebook::react::CallInvoker> &)callinvoker {
  try {
    opserver::install(runtime, callinvoker);
    _didInstall = true;
  } catch (const std::exception &exc) {
    _didInstall = false;
  }
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params {
  return std::make_shared<facebook::react::NativeOpServerSpecJSI>(params);
}

//+ (NSString *)moduleName {
//  return @"OpServer";
//}

- (nonnull NSNumber *)install { 
  return @1;
}

@end
