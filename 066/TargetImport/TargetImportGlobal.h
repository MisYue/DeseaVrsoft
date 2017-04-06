#pragma once
#ifndef TARGETIMPORT_EXE
#ifdef TARGETIMPORT_EXPORTS
#define TARGETIMPORT_API __declspec(dllexport)
#else
#define TARGETIMPORT_API __declspec(dllimport)
#endif
#else 
#define TARGETIMPORT_API
#endif
