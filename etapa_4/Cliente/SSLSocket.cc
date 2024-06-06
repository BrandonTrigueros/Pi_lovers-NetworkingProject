#include <openssl/ssl.h>
#include <openssl/err.h>

#include <stdexcept>

#include "SSLSocket.h"
#include "Socket.h"

SSLSocket::SSLSocket(bool IPv6) {
  this->InitVSocket('s', IPv6);
  this->SSLContext = nullptr;
  this->SSLStruct = nullptr;
  this->Init(); // Initializes to client context
}

SSLSocket::SSLSocket(char *certFileName, char *keyFileName, bool IPv6) {
}

SSLSocket::SSLSocket(int id) {
  this->InitVSocket(id);
}

SSLSocket::~SSLSocket() {
  if (nullptr != this->SSLContext) {
    SSL_CTX_free(reinterpret_cast<SSL_CTX *>(this->SSLContext));
  }
  if (nullptr != this->SSLStruct) {
    SSL_free(reinterpret_cast<SSL *>(this->SSLStruct));
  }
  Close();
}

void SSLSocket::Init(bool serverContext) {
  this->InitContext(serverContext);
  SSL *ssl = SSL_new((SSL_CTX *)this->SSLContext);
  if (nullptr == ssl) {
    throw std::runtime_error("SSLSocket::Init( bool )");
  }
  this->SSLStruct = (void *)ssl;
}

void SSLSocket::InitContext(bool serverContext) {
  SSL_library_init();
  SSL_load_error_strings();
  const SSL_METHOD *method = TLS_client_method();
  if (nullptr == method) {
    throw std::runtime_error("SSLSocket::method");
  }
  SSL_CTX *context = SSL_CTX_new(method);
  if (0 == context) {
    throw std::runtime_error("SSLSocket::context");
  }
  this->SSLContext = (void *)context;
}


void SSLSocket::LoadCertificates(const char *certFileName, const char *keyFileName) {
}

int SSLSocket::Connect(const char *hostName, int port) {
  int operation_result;
  operation_result = this->DoConnect(hostName, port); // Establish a non ssl connection first
  if (operation_result == -1) {
    throw(std::runtime_error("VSocket::Connect, DoConnect"));
  }
  operation_result = SSL_set_fd((SSL *)this->SSLStruct, this->idSocket);
  if (operation_result == 0) {
    throw std::runtime_error("VSocket::Connect, SSL_set_fd");
  }
  operation_result = SSL_connect((SSL *)this->SSLStruct);
  // check for errors
  if (operation_result <= 0) {
    throw std::runtime_error("VSocket::Connect, SSL_connect");
  }
  return operation_result;
}

int SSLSocket::Connect(const char *host, const char *service) {
  int operation_result;
  operation_result = this->DoConnect(host, service);
  if (operation_result == -1) {
    throw(std::runtime_error("VSocket::Connect, DoConnect"));
  }
  operation_result = SSL_set_fd((SSL *)this->SSLStruct, this->idSocket);
  if (operation_result == 0) {
    throw std::runtime_error("VSocket::Connect, SSL_set_fd");
  }
  operation_result = SSL_connect((SSL *)this->SSLStruct);
  if (operation_result <= 0) {
    throw std::runtime_error("VSocket::Connect, SSL_connect");
  }
  return operation_result;
}

size_t SSLSocket::Read(void *buffer, size_t size) {
  int operation_result = SSL_read((SSL *)this->SSLStruct, buffer, size);
  if (operation_result == -1) {
    throw std::runtime_error("SSLSocket::Read( void *, size_t )");
  }
  return operation_result;
}

size_t SSLSocket::Write(const char *string) {
  int operation_result = SSL_write((SSL *)this->SSLStruct, string, strlen(string));
  if (operation_result == -1) {
    perror("SSLSocket::Write");
    printf("ST: %d", operation_result);
    throw std::runtime_error("SSLSocket::Write( const char * )");
  }
  return operation_result;
}

size_t SSLSocket::Write(const void *buffer, size_t size) {
  int operation_result = SSL_write((SSL *)this->SSLStruct, buffer, size);
  if (operation_result == -1) {
    throw std::runtime_error("SSLSocket::Write( void *, size_t )");
  }
  return operation_result;
}

SSLSocket *SSLSocket::Accept() {
  int id, operation_result;
  SSLSocket *ssl;
  if (operation_result <= 0) {
    throw std::runtime_error("SSLSocket::Accept()");
  }
  return ssl;
}

void SSLSocket::ShowCerts() {
  X509 *cert;
  char *line;
  cert = SSL_get_peer_certificate((SSL *)this->SSLStruct); // Get certificates (if available)
  if (cert != nullptr) {
    printf("Server certificates:\n");
    line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
    printf("Subject: %s\n", line);
    free(line);
    line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
    printf("Issuer: %s\n", line);
    free(line);
    X509_free(cert);
  } else {
    printf("No certificates.\n");
  }
}

const char *SSLSocket::GetCipher() {
  return SSL_get_cipher(reinterpret_cast<SSL *>(this->SSLStruct));
}