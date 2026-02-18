//
// Copyright (c) 2016 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
// MIT LICENSE:
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define AP_KEY "AA1027cp"
#define EMPTY 0xFFFFFFFF
#define PROPERTYNAMESIZE 16
#define DIGEST_SIZE 20
#define XML_MAX_LINE 16384
#define CURRENT_BLOB_FILE_VERSION (1)

// Enumerators
typedef enum PRIVACYTYPES {
	Undefined = 0,
	Defined = 1, // 0x0001
	ProfilesOnly = 3, // 0x0011
	ApplicationsOnly = 5, // 0x0101
	ApplicationsAndProfiles = 7 // 0x0111
} PRIVACYTYPES;

typedef enum DATATYPES {
	DT_Unknown = 0,
	DT_Binary,
	DT_Qword,
	DT_Dword,
	DT_Boolean,
	DT_Enumerated,
	DT_Stringed
} DATATYPES;

// Common typedef's for transitional and compacts

typedef struct TABLES {
	unsigned int Offset; // In units of QWORDs relative to start of Buffer
	unsigned int Length; // In units of QWORDs relative to start of Buffer
} TABLES;

typedef struct STRINGS {
	unsigned int Offset; // In units of QWORDs relative to start of Buffer
	unsigned int Length; // In units of BYTES relative to start of Buffer, not including NUL in case of "wchar_ts" (though buffer contains it)
} STRINGS;

typedef struct ELEMENTS {
	unsigned int Index; // In units of QWORDs relative to start of Buffer
} ELEMENTS;

typedef struct BLOBS {
	unsigned int Size; // In units of QWORDs of the VALUE of this datum
} BLOBS;

// interim typedef's

typedef struct DRIVER {
	wchar_t* NameOfDriver;
	PRIVACYTYPES Privacy;

	STRINGS strsNameOfDriver;
	ELEMENTS elmDriver;
} DRIVER;

typedef struct PROPERTY {
	DATATYPES DataType;
	wchar_t* NameOfProperty;
	wchar_t* SetOfValidEnumStringsTokenised;
	struct PROPERTY* NextProperty;

	STRINGS strsNameOfProperty;
	STRINGS strsSetOfValidEnumStringsTokenised;
	ELEMENTS elmProperty;
} PROPERTY;

typedef struct AREA {
	DRIVER* DriverComponent;
	PROPERTY* HeadProperty;
	struct AREA* NextArea;
	ELEMENTS elmArea;
} AREA;

typedef struct VALUE {
	wchar_t* DataOfValue; // this is the data of the value, a text node in XML
	int iLengthOfValue; // Length of Value in sizeof(wchar_t)
	PROPERTY* PropertyOfValue; // pointer to the actual property entry
	struct VALUE* NextValue;

	STRINGS strsDataOfValue;
} VALUE;

typedef struct PROFILE {
	DRIVER* DriverThisProfileBelongsTo;
	wchar_t* NameOfThisProfile;
	wchar_t* NotesAboutThisProfile;
	VALUE* HeadValue;
	struct PROFILE* NextProfile;

	// store strings offset and length
	STRINGS strsNameOfThisProfile;
	STRINGS strsNotesAboutThisProfile;
	ELEMENTS elmProfile;
} PROFILE;

typedef struct USE {
	wchar_t* NameOfTheProfileToUse;
	DRIVER* DriverOfTheProfileToUse; // normalized pointer
	struct USE* NextUse;

	STRINGS strsNameOfTheProfileToUse;
	ELEMENTS elmUse;
} USE;

typedef struct APPLICATION {
	wchar_t* TitleOfApplicationRecord; // "named string"
	wchar_t* FilenameOfThisApplication; // "general string"
	wchar_t* PartialPathOfApplication; // "general string"
	wchar_t* Version; // "numerical string" ???
	USE* HeadUse;
	struct APPLICATION* NextApplication;

	STRINGS strsTitleOfApplicationRecord; // "named string"
	STRINGS strsFilenameOfThisApplication; // "general string"
	STRINGS strsPartialPathOfApplication; // "general string"
	STRINGS strsVersion; // "numerical string" ???
	ELEMENTS elmApplication;
} APPLICATION;

typedef struct CUSTOMISATIONS {
	AREA* HeadArea;
	PROFILE* HeadProfile;
	APPLICATION* HeadApplication;
	wchar_t* Content;
	wchar_t* Release;
	wchar_t* Format;

	STRINGS strsContent;
	STRINGS strsRelease;
	STRINGS strsFormat;
} CUSTOMISATIONS;

// Start of compact data types

typedef struct DRIVER_COMPACT {
	STRINGS NameOfThisDriver;
	PRIVACYTYPES Privacy;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) DRIVER_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} DRIVER_COMPACT;
#endif

typedef struct PROPERTY_COMPACT {
	DATATYPES DataTypeOfThisProperty;
	STRINGS NameOfThisProperty;
	STRINGS SetOfValidEnumeratedStringsTokenised;
	ELEMENTS NextPropertyForThisDriver;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) PROPERTY_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} PROPERTY_COMPACT;
#endif

typedef struct AREA_COMPACT {
	ELEMENTS TheDriverThisSetOfAreaBelongsTo;
	ELEMENTS FirstPropertyForThisDriver;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) AREA_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} AREA_COMPACT;
#endif

typedef struct VALUE_COMPACT {
	char NameOfThisProperty[PROPERTYNAMESIZE];
	BLOBS ValueSizeFollowedByActualDatum;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) VALUE_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} VALUE_COMPACT;
#endif

typedef struct PROFILE_COMPACT {
	ELEMENTS TheDriverThisProfileBelongsTo;
	STRINGS NameOfThisProfile;
	STRINGS NotesAboutThisProfile;
	ELEMENTS FirstNameValuePairForThisProfile;
	unsigned int AggregateSizeOfTheValues;
	unsigned int NumberOfValuesInThisProfile;
	struct VALUE_COMPACT FirstValueOfThisProfile;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) PROFILE_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} PROFILE_COMPACT;
#endif

typedef struct USE_COMPACT {
	ELEMENTS TheProfileToUse;
	ELEMENTS NextUseForThisApplication;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) USE_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} USE_COMPACT;
#endif

typedef struct APPLICATION_COMPACT {
	STRINGS TitleGivenToThisApplicationRecord;
	STRINGS FilenameOfThisApplication;
	STRINGS PartialPathWhereThisApplicationResides;
	STRINGS VersionNumberOfThisApplication;
	ELEMENTS FirstUseForThisApplication;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) APPLICATION_COMPACT; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} APPLICATION_COMPACT;
#endif

typedef struct BODY {
	TABLES Words;
	TABLES Driver;
	TABLES Property;
	TABLES Area;
	TABLES Profile;
	TABLES Use;
	TABLES Application;
	unsigned long long Buffer[1];
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) BODY; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} BODY;
#endif

typedef struct HEADER {
	unsigned char PreAmble[4];
	unsigned int Version;
	unsigned char Digest[DIGEST_SIZE];
	STRINGS Release;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) HEADER; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} HEADER;
#endif

typedef struct BINFILE {
	HEADER Header;
	BODY Body;
#if defined (LINUX)
} __attribute__((packed)) __attribute__((aligned(1))) BINFILE; // This is needed for Linux because structure is aligned different from Windows by default. Using single byte alignment to match Windows
#else
} BINFILE;
#endif

// end of all data types

// Local structures
// Internal type used to store interim string table and used for look up.
typedef struct WORDITEM {
	wchar_t* WordItem; // one actual array item data, can add more of these if needed
	STRINGS Strings; // STRINGS representation of the string in the local COMPACT string table
} WORDITEM;

#endif /* STRUCTURES_H_ */