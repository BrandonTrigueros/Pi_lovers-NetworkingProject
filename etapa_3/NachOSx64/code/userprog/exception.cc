// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "syscall.h"
#include "system.h"
#include <fcntl.h>
#include <directory.h>
#include <synch.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

Semaphore *console_sem = new Semaphore("Console", 1);

void returnFromSystemCall()
{
  machine->WriteRegister(
      PrevPCReg, machine->ReadRegister(PCReg)); // PrevPC <- PC
  machine->WriteRegister(
      PCReg, machine->ReadRegister(NextPCReg)); // PC <- NextPC
  machine->WriteRegister(
      NextPCReg, machine->ReadRegister(NextPCReg) + 4); // NextPC <- NextPC + 4
} // returnFromSystemCall

/*
 *  System call interface: Halt()
 */
void NachOS_Halt()
{ // System call 0
  DEBUG('a', "Shutdown, initiated by user program.\n");
  interrupt->Halt();
}

/*
 *  System call interface: void Exit( int )
 */
void NachOS_Exit()
{ // System call 1
}

/*
 *  System call interface: SpaceId Exec( char * )
 */
void NachOS_Exec()
{ // System call 2
}

/*
 *  System call interface: int Join( SpaceId )
 */
void NachOS_Join()
{ // System call 3
}

/*
 *  System call interface: void Create( char * )
 */
void NachOS_Create()
{ // System call 4
}

/*
 *  System call interface: OpenFileId Open( char * )
 */
void NachOS_Open() { // System call 5 
}

/*
 *  System call interface: OpenFileId Write( char *, int, OpenFileId )
 */
void NachOS_Write()
{ // System call 6
  char *buffer = NULL;
  int name = machine->ReadRegister(4); // Read address of buffer
  int size = machine->ReadRegister(5); // Read size to write
  buffer = new char[size + 1];
  // buffer = Read data from address given by user;
  for (int i = 0; i < size; i++)
  {
    machine->ReadMem(name + i, 1, (int *)&buffer[i]);
    if (buffer[i] == '\n')
    {
      buffer[i + 1] = '\0';
      break;
    }
  }
  OpenFileId descriptor = machine->ReadRegister(6); // Read file descriptor

  // Need a semaphore to synchronize access to console
  console_sem->P(); // Wait until it is safe to write
  switch (descriptor)
  {
  case ConsoleInput: // User could not write to standard input
    machine->WriteRegister(2, -1);
    break;
  case ConsoleOutput:
    buffer[size] = 0;
    printf("%s", buffer);
    break;
  case ConsoleError: // This trick permits to write integers to console
    printf("%d\n", machine->ReadRegister(4));
    break;
  default: // All other opened files
           // Verify if the file is opened, if not return -1 in r2
    if (currentThread->openFilesTable->isOpened(descriptor))
    {
      // Get the unix handle from our table for open files
      int unixHandle = currentThread->openFilesTable->getUnixHandle(descriptor);
      // Do the write to the already opened Unix file
      write(unixHandle, buffer, size);
      // Return the number of chars written to user, via r2
      machine->WriteRegister(2, size);
    }
    else
    {
      machine->WriteRegister(2, -1);
    }
    break;
  }
  // Update simulation stats, see details in Statistics class in
  // machine/stats.cc
  stats->numConsoleCharsWritten += size;
  console_sem->V(); // Signal that we have finished writing

  delete[] buffer;
  returnFromSystemCall(); // Update the PC registers
}

/*
 *  System call interface: OpenFileId Read( char *, int, OpenFileId )
 */
void NachOS_Read() { // System call 7
  char *buffer = NULL;
  int name = machine->ReadRegister(4); // Read address of buffer
  int size = machine->ReadRegister(5); // Read size to write

  buffer = new char[size + 1];
  OpenFileId fileDescriptor = machine->ReadRegister(6); // Read file descriptor

  // Needs a semaphore to synchronize access to console
  console_sem->P(); // Wait until it is safe to write

  switch (fileDescriptor) {
  case ConsoleInput:
    for (int i = 0; i < size; i++) {
      buffer[i] = getchar();
      if (buffer[i] == '\n') {
        buffer[i + 1] = '\0';
        break;
      }
    }
    buffer[size] = '\0';
    for (int i = 0; i < size; i++) {
      machine->WriteMem(name + i, 1, buffer[i]);
    }
    machine->WriteRegister(2, size);
    break;

  case ConsoleOutput: // User could not read from standard output
    machine->WriteRegister(2, -1);
    break;

  case ConsoleError:
    printf("%d\n", machine->ReadRegister(4));
    break;

  default: // All other opened files
    // Verify if the file is opened, if not return -1 in r2
    if (currentThread->openFilesTable->isOpened(fileDescriptor)) {
      // Get the unix handle from our table for open files
      int unixHandle = currentThread->openFilesTable->getUnixHandle(fileDescriptor);
      // Do the write to the already opened Unix file
      int readResult = read(unixHandle, buffer, size);
      if (readResult == -1) {
        machine->WriteRegister(2, -1);
      } else {
        buffer[readResult] = '\0';
        for (int i = 0; i < readResult; i++) {
          machine->WriteMem(name + i, 1, buffer[i]);
        }
        machine->WriteRegister(2, readResult);
      }
    } else {
      machine->WriteRegister(2, -1);
    }
    break;
  }
  // Update simulation stats, see details in Statistics class in machine/stats.cc
  stats->numConsoleCharsRead += size;
  console_sem->V(); // Signal that we have finished writing

  delete[] buffer;
  returnFromSystemCall(); // Update the PC registers
}

/*
 *  System call interface: void Close( OpenFileId )
 */
void NachOS_Close()
{ // System call 8
}

/*
 *  System call interface: void Fork( void (*func)() )
 */
void NachOS_Fork()
{ // System call 9
}

/*
 *  System call interface: void Yield()
 */
void NachOS_Yield()
{ // System call 10
}

/*
 *  System call interface: Sem_t SemCreate( int )
 */
void NachOS_SemCreate()
{ // System call 11
}

/*
 *  System call interface: int SemDestroy( Sem_t )
 */
void NachOS_SemDestroy()
{ // System call 12
}

/*
 *  System call interface: int SemSignal( Sem_t )
 */
void NachOS_SemSignal()
{ // System call 13
}

/*
 *  System call interface: int SemWait( Sem_t )
 */
void NachOS_SemWait()
{ // System call 14
}

/*
 *  System call interface: Lock_t LockCreate( int )
 */
void NachOS_LockCreate()
{ // System call 15
}

/*
 *  System call interface: int LockDestroy( Lock_t )
 */
void NachOS_LockDestroy()
{ // System call 16
}

/*
 *  System call interface: int LockAcquire( Lock_t )
 */
void NachOS_LockAcquire()
{ // System call 17
}

/*
 *  System call interface: int LockRelease( Lock_t )
 */
void NachOS_LockRelease()
{ // System call 18
}

/*
 *  System call interface: Cond_t LockCreate( int )
 */
void NachOS_CondCreate()
{ // System call 19
}

/*
 *  System call interface: int CondDestroy( Cond_t )
 */
void NachOS_CondDestroy()
{ // System call 20
}

/*
 *  System call interface: int CondSignal( Cond_t )
 */
void NachOS_CondSignal()
{ // System call 21
}

/*
 *  System call interface: int CondWait( Cond_t )
 */
void NachOS_CondWait()
{ // System call 22
}

/*
 *  System call interface: int CondBroadcast( Cond_t )
 */
void NachOS_CondBroadcast()
{ // System call 23
}

/*
 *  System call interface: Socket_t Socket( int, int )
 */
void NachOS_Socket() { // System call 30
  int family = machine->ReadRegister(4); 
  int type = machine->ReadRegister(5);
  family == AF_INET_NachOS ? family = AF_INET : AF_INET6;
  type == SOCK_STREAM_NachOS ? type =  SOCK_STREAM : SOCK_DGRAM;

  int unixID = socket(family, type, 0);
  int fileDescriptor = currentThread->openFilesTable->Open(unixID);
  
  machine->WriteRegister(2, fileDescriptor);
  returnFromSystemCall();
}

/*
 *  System call interface: Socket_t Connect( char *, int )
 */
void NachOS_Connect() { // System call 31
    char* buffer = new char[128];
    int socketID = machine->ReadRegister(4);
    int socketIP = machine->ReadRegister(5);
    int socketPort = machine->ReadRegister(6);

    for (int i = 0; i < 128; i++) {
      machine->ReadMem(socketIP + i, 1, (int*)&buffer[i]);
      if (buffer[i] == '\0') {
          break;
      }
    }

    int socketDescriptor = currentThread->openFilesTable->getUnixHandle(socketID);

    struct sockaddr_in hostAddress;
    memset((char*) &hostAddress, 0, sizeof(hostAddress));
    hostAddress.sin_family = AF_INET;
    int operationResult;
    operationResult = inet_pton(AF_INET, buffer, &hostAddress.sin_addr);
    if ( -1 == operationResult ) {
      machine->WriteRegister(2, -1);
    }
    hostAddress.sin_port = htons(socketPort);

    operationResult = connect(socketDescriptor, (sockaddr*) &hostAddress, sizeof(hostAddress));
    if ( operationResult == - 1) {
      machine->WriteRegister(2, -1);
    } else {
      machine->WriteRegister(2, operationResult);
    }

    delete[] buffer;
    returnFromSystemCall();
}

/*
 *  System call interface: int Bind( Socket_t, int )
 */
void NachOS_Bind()
{ // System call 32
}

/*
 *  System call interface: int Listen( Socket_t, int )
 */
void NachOS_Listen()
{ // System call 33
}

/*
 *  System call interface: int Accept( Socket_t )
 */
void NachOS_Accept()
{ // System call 34
}

/*
 *  System call interface: int Shutdown( Socket_t, int )
 */
void NachOS_Shutdown()
{ // System call 25
}

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which)
{
  int type = machine->ReadRegister(2);

  switch (which)
  {

  case SyscallException:
    switch (type)
    {
    case SC_Halt: // System call # 0
      NachOS_Halt();
      break;
    case SC_Exit: // System call # 1
      NachOS_Exit();
      break;
    case SC_Exec: // System call # 2
      NachOS_Exec();
      break;
    case SC_Join: // System call # 3
      NachOS_Join();
      break;

    case SC_Create: // System call # 4
      NachOS_Create();
      break;
    case SC_Open: // System call # 5
      NachOS_Open();
      break;
    case SC_Read: // System call # 6
      NachOS_Read();
      break;
    case SC_Write: // System call # 7
      NachOS_Write();
      break;
    case SC_Close: // System call # 8
      NachOS_Close();
      break;

    case SC_Fork: // System call # 9
      NachOS_Fork();
      break;
    case SC_Yield: // System call # 10
      NachOS_Yield();
      break;

    case SC_SemCreate: // System call # 11
      NachOS_SemCreate();
      break;
    case SC_SemDestroy: // System call # 12
      NachOS_SemDestroy();
      break;
    case SC_SemSignal: // System call # 13
      NachOS_SemSignal();
      break;
    case SC_SemWait: // System call # 14
      NachOS_SemWait();
      break;

    case SC_LckCreate: // System call # 15
      NachOS_LockCreate();
      break;
    case SC_LckDestroy: // System call # 16
      NachOS_LockDestroy();
      break;
    case SC_LckAcquire: // System call # 17
      NachOS_LockAcquire();
      break;
    case SC_LckRelease: // System call # 18
      NachOS_LockRelease();
      break;

    case SC_CondCreate: // System call # 19
      NachOS_CondCreate();
      break;
    case SC_CondDestroy: // System call # 20
      NachOS_CondDestroy();
      break;
    case SC_CondSignal: // System call # 21
      NachOS_CondSignal();
      break;
    case SC_CondWait: // System call # 22
      NachOS_CondWait();
      break;
    case SC_CondBroadcast: // System call # 23
      NachOS_CondBroadcast();
      break;

    case SC_Socket: // System call # 30
      NachOS_Socket();
      break;
    case SC_Connect: // System call # 31
      NachOS_Connect();
      break;
    case SC_Bind: // System call # 32
      NachOS_Bind();
      break;
    case SC_Listen: // System call # 33
      NachOS_Listen();
      break;
    case SC_Accept: // System call # 32
      NachOS_Accept();
      break;
    case SC_Shutdown: // System call # 33
      NachOS_Shutdown();
      break;

    default:
      printf("Unexpected syscall exception %d\n", type);
      ASSERT(false);
      break;
    }
    break;

  case PageFaultException:
  {
    break;
  }

  case ReadOnlyException:
    printf("Read Only exception (%d)\n", which);
    ASSERT(false);
    break;

  case BusErrorException:
    printf("Bus error exception (%d)\n", which);
    ASSERT(false);
    break;

  case AddressErrorException:
    printf("Address error exception (%d)\n", which);
    ASSERT(false);
    break;

  case OverflowException:
    printf("Overflow exception (%d)\n", which);
    ASSERT(false);
    break;

  case IllegalInstrException:
    printf("Ilegal instruction exception (%d)\n", which);
    ASSERT(false);
    break;

  default:
    printf("Unexpected exception %d\n", which);
    ASSERT(false);
    break;
  }
}
