/**
 *
 *   UCR-ECCI
 *   SSL Socket class interface
 *
 **/

#ifndef SSLSocket_h
#define SSLSocket_h

#include <iostream>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdexcept>

#include "VSocket.h"

class SSLSocket : public VSocket {

  private:
  // Instance variables
  void* SSLContext;  // SSL context
  void* SSLStruct;  // SSL BIO (Basic Input/Output)

  // Methods
  public:
  SSLSocket(bool IPv6 = false);
  SSLSocket(char*, char*, bool = false);
  SSLSocket(int);
  ~SSLSocket();

  public:
  int Connect(const char*, int);
  int Connect(const char*, const char*);

  size_t Read(void*, size_t);
  size_t Write(const char*);
  size_t Write(const void*, size_t);

  SSLSocket* Accept();
  void ShowCerts();
  const char* GetCipher();
  void LoadCertificates(const char*, const char*);

  private:
  void Init(bool = false);
  void InitContext(bool);
};

#endif
