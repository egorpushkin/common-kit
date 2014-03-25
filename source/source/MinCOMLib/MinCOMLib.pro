# -------------------------------------------------
# MinCOMLib Project File
# -------------------------------------------------
TARGET = MinCOM
TEMPLATE = lib
CONFIG += staticlib
win32 { 
    CONFIG(release, debug|release) {
        OBJECTS_DIR = ../../compiled/mingw/MinCOMLib/release
        DESTDIR = ../../lib/mingw/release
    }
    CONFIG(debug, debug|release) {
        OBJECTS_DIR = ../../compiled/mingw/MinCOMLib/debug
        DESTDIR = ../../lib/mingw/debug
    }
}
macx { 
    CONFIG(release, debug|release) {
        OBJECTS_DIR = ../../compiled/macx/MinCOMLib/release
        DESTDIR = ../../lib/macx/release
    }
    CONFIG(debug, debug|release) {
        OBJECTS_DIR = ../../compiled/macx/MinCOMLib/debug
        DESTDIR = ../../lib/macx/debug
    }
}

clang {
    # Disable some harmless warnings
    QMAKE_CXXFLAGS_WARN_ON += -Wno-parentheses-equality
    QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
    QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-private-field

    # Disable optimizations in release mode.
    # As annoying as it sounds some clang optimizations break boost::asio.
    QMAKE_CXXFLAGS_RELEASE -= -O2
}

INCLUDEPATH = ../../../../boost \
    ../../include \
    ../../sdk/include
PRECOMPILED_HEADER = Common/Common.h
HEADERS += Common/Common.h \
    Commands/Commands.h \
    Commands/DCommandsStub.h \
    Concurrency/Jobs/JobsContext.h \
    Concurrency/Jobs/JobsQueue.h \
    Concurrency/Locks/ReadWriteLock.h \
    Concurrency/Core/Thread.h \
    Concurrency/Core/Semaphore.h \
    Concurrency/Core/Mutex.h \
    Concurrency/Core/Event.h \
    Container/Vector.h \
    Container/List.h \
    Container/Iterator.h \
    Container/IPrivateIterator.h \
    Container/VectorEnumerator.h \
    Events/AccessPointImpl.h \
    Events/EventsSpreader.h \
    Network/Core/TCPConnection.h \
    Network/Core/Service.h \
    Network/Core/DServerStub.h \
    Network/Core/DRawDataStub.h \
    Network/Core/TCPServer.h \
    Network/Core/NetworkStats.h \
    Network/Protocol/DProtocolStub.h \
    Network/Protocol/Protocol.h \
    Log/LogStorage.h \
    ../../include/MinCOM/Common/ToolsMap.h \
    ../../include/MinCOM/Common/Object.h \
    ../../include/MinCOM/Common/MethodWrapper.h \
    ../../include/MinCOM/Common/ICommon.h \
    ../../include/MinCOM/Common/Guid.h \
    ../../include/MinCOM/Common/Errors.h \
    ../../include/MinCOM/Common/CommonImpl.h \
    ../../include/MinCOM/Common/Common.h \
    ../../include/MinCOM/Common/Class.h \
    ../../include/MinCOM/Common/Call.h \
    ../../include/MinCOM/Concurrency/Interfaces/IThread.h \
    ../../include/MinCOM/Concurrency/Interfaces/ISynchro.h \
    ../../include/MinCOM/Concurrency/Interfaces/ISemaphore.h \
    ../../include/MinCOM/Concurrency/Interfaces/IRunnable.h \
    ../../include/MinCOM/Concurrency/Interfaces/IReadWriteLock.h \
    ../../include/MinCOM/Concurrency/Interfaces/IMutex.h \
    ../../include/MinCOM/Concurrency/Interfaces/IJobsQueue.h \
    ../../include/MinCOM/Concurrency/Interfaces/IEvent.h \
    ../../include/MinCOM/Pointers/Weak.h \
    ../../include/MinCOM/Pointers/Strong.h \
    ../../include/MinCOM/Pointers/StdExtensions.h \
    ../../include/MinCOM/Pointers/DualRefCounter.h \
    ../../include/MinCOM/Pointers/BinaryOperators.h \
    ../../include/MinCOM/Network/Protocol/IMessage.h
SOURCES += Common/GuidsInternal.cpp \
    Common/Guids.cpp \
    Common/Errors.cpp \
    Common/Defaults.cpp \
    Common/Common.cpp \
    Common/Call.cpp \
    Common/Object.cpp \
    Commands/DCommandsStub.cpp \
    Commands/Commands.cpp \
    Concurrency/Jobs/JobsQueue.cpp \
    Concurrency/Jobs/JobsContext.cpp \
    Concurrency/Locks/ReadWriteLock.cpp \
    Container/VectorEnumerator.cpp \
    Container/Vector.cpp \
    Container/List.cpp \
    Events/EventsSpreader.cpp \
    Events/Events.cpp \
    Events/AccessProviderImpl.cpp \
    Events/AccessPointImpl.cpp \
    External/StrongPtr.cpp \
    External/SmartPtr.cpp \
    External/SmallObj.cpp \
    External/Singleton.cpp \
    External/SafeFormat.cpp \
    External/OrderedStatic.cpp \
    Factory/FactoryImpl.cpp \
    Factory/FactoryHolder.cpp \
    Factory/Library.cpp \
    Network/Core/TCPServer.cpp \
    Network/Core/TCPConnection.cpp \
    Network/Core/Service.cpp \
    Network/Core/DServerStub.cpp \
    Network/Core/DRawDataStub.cpp \
    Network/Protocol/Protocol.cpp \
    Network/Protocol/MessageImpl.cpp \
    Network/Protocol/DProtocolStub.cpp \
    Variant/Accessors.cpp \
    Variant/Constructors.cpp \
    Log/LogStorage.cpp \
    Log/LogRoutine.cpp \
    Log/Log.cpp \
    Log/LogStatement.cpp \
    Concurrency/Scopes/SemaphoreScopeRelease.cpp \
    Common/GuidImpl.cpp \
    Concurrency/Scopes/MutexScope.cpp \
    External/error_code.146.cpp \
    Network/Core/NetworkStats.cpp
win32 { 
    HEADERS += Platforms/win32/Concurrent.win32.h \
        Platforms/win32/Locale.win32.h
    SOURCES += Concurrency/Core/Mutex.win32.cpp \
        Concurrency/Core/IThread.win32.cpp \
        Concurrency/Core/Thread.win32.cpp \
        Concurrency/Core/Semaphore.win32.cpp \
        Platforms/win32/Locale.win32.cpp \
        Platforms/win32/Concurrent.win32.cpp
}
unix {
    SOURCES += Concurrency/Core/Mutex.posix.cpp \
        Concurrency/Core/IThread.posix.cpp \
        Concurrency/Core/Thread.posix.cpp \
        Concurrency/Core/Semaphore.posix.cpp
}
