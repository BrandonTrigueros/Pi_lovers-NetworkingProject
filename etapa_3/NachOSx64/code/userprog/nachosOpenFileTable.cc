#include "nachosOpenFileTable.h"
#include "bitmap.h"

// Initialize the table and usage counter
NachosOpenFilesTable::NachosOpenFilesTable() {
  this->openFilesMap = new BitMap(MAX_FILE_DESCRIPTORS);
  this->usage = 0;
  this->openFiles = new int[MAX_FILE_DESCRIPTORS];
  memset(this->openFiles, -1, MAX_FILE_DESCRIPTORS);

  this->openFiles[0] = 0;
  this->openFiles[1] = 1;
  this->openFiles[2] = 2;
  this->openFilesMap->Mark(0);
  this->openFilesMap->Mark(1);
  this->openFilesMap->Mark(2);
}

// Deallocate memory used by the table
NachosOpenFilesTable::~NachosOpenFilesTable() {
  delete[] this->openFiles;
  delete this->openFilesMap;
  this->usage = 0;
}

// Register a new file handle
int NachosOpenFilesTable::Open(int UnixHandle) {
  // Find a free slot in the table
  int freeSlot = this->openFilesMap->Find();
  if (freeSlot == -1) {
    return -1;  // No free slots available
  }
  this->openFiles[freeSlot] = UnixHandle;
  return freeSlot;  // Return the assigned Nachos handle
}

// Unregister a file handle
int NachosOpenFilesTable::Close(int NachosHandle) {
  if (!isOpened(NachosHandle)) {
    return -1;  // Handle not found
  }

  int unixHandle = this->openFiles[NachosHandle] = -1;
  this->openFilesMap->Clear(NachosHandle);
  this->openFilesMap[NachosHandle] = -1;
  return unixHandle;
}

// Check if a Nachos handle is open
bool NachosOpenFilesTable::isOpened(int NachosHandle) {
  return this->openFilesMap->Test(NachosHandle);
}

// Get the underlying Unix handle for a Nachos handle
int NachosOpenFilesTable::getUnixHandle(int NachosHandle) {
  if (!isOpened(NachosHandle)) {
    return -1;  // Handle not found
  }

  return this->openFiles[NachosHandle];
}

// Increment usage counter when a thread starts using the table
void NachosOpenFilesTable::addThread() { this->usage++; }

// Decrement usage counter when a thread finishes using the table
void NachosOpenFilesTable::delThread() {
  if (usage > 0) {
    this->usage--;
  }
}

// Print table contents (optional, for debugging)
void NachosOpenFilesTable::Print() {
  printf("Nachos Open File Table:\n");
  for (int i = 0; i < MAX_FILE_DESCRIPTORS; i++) {
    printf("  Nachos Handle: %d, Unix Handle: %d\n", i, this->openFiles[i]);
  }
}
