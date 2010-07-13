/*
 * File name   : Config.h
 *
 * Copyright (c) 2009 Scientific Software
 *
 * Modification History:
 * Date        Name                Description
 * 2009-03-17  Egor Pushkin        Initial version
 */

#ifndef CONFIG_H__MINCOM__INCLUDED_
#define CONFIG_H__MINCOM__INCLUDED_

// Version Information
//////////////////////////////////////////////////////////////////////////

/** Defines human readable MinCOM version. */
#define MC_VERSION std::string("0.1.0")

// Debugging
//////////////////////////////////////////////////////////////////////////
#if defined(DEBUG) || defined(_DEBUG)
#define MC_DEBUG
#else
#define MC_RELEASE
#endif

// Logging
//////////////////////////////////////////////////////////////////////////

/** 
 * Disables logging on mobile devices. Logging feature generally significantly
 * slows down application performance due to frequent calls to storage subsystem
 * which is rather slow on mobile devices. Another reason is that sometimes it 
 * is impossible to access logs on the device.
 *
 * TODO: Implement asynchronous logging over TCP/IP as an option. 
 */
#if defined(MC_PLATFORM_MOBILE) || !defined(MC_DEBUG)
#define MC_DISABLE_LOG
#endif

#endif // !CONFIG_H__MINCOM__INCLUDED_
