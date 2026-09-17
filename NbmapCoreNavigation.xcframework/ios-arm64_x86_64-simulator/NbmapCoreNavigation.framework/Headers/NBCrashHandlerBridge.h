#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Installs the process-wide navigation crash handlers. The descriptor must
/// already be open for append-only writes and must remain open until uninstall.
FOUNDATION_EXPORT BOOL NBCrashHandlerBridgeInstall(int fileDescriptor);

/// Restores every handler that was present when install was called. A handler
/// replaced by the host after installation is left untouched.
FOUNDATION_EXPORT void NBCrashHandlerBridgeUninstall(void);

/// Internal diagnostics used by the Swift owner and unit tests.
FOUNDATION_EXPORT BOOL NBCrashHandlerBridgeIsInstalled(void);
FOUNDATION_EXPORT BOOL NBCrashHandlerBridgeOwnsExceptionHandler(void);
FOUNDATION_EXPORT BOOL NBCrashHandlerBridgeOwnsSignal(int signalNumber);

NS_ASSUME_NONNULL_END
