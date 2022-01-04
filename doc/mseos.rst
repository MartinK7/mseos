System listing:
=================

Systém dokáže mountovat pouze kořenové adresáře. Název adresáře je před znakem ':'.
Každý kořenový adresář má přiřazen v jádře "fsdriver", který poskytuje patřičné informace o obsahu.
Kdaždý fsdriver má možnost být přiřazen k nějakému device file, tak aby mohl číst data ze zařízení.

Stat files @ stat:*
-------------
stat:proc		Catnutím vytiskne procesy/podprocesy + statistika mem/cpu
stat:memory		Catnutím vytiskne zbývající volnou paměť
stat:mounts		Catnutím vytiskne seznam namounotvaných fs systémů (mem0->fs0 mmc0->fs1)

Device file @ dev:*
-----------------------
dev:zero
dev:null
dev:rand
dev:fb0
dev:pointer0
dev:console0
dev:mem0
dev:gpio0
dev:mmc0

Ukázka listování obsahu @ *:**/*.*
==================
fs0:file.ef
fs1:ahoj/hello.txt

System calls
============
Operace se souborovým systémem:
-------------------------------
MOUNT		device	rootname	RETURN syscode		example: MOUNT "mem0" "fs0"	SYSCODE_OK
UNMOUNT		rootname		RETURN syscode		example: UNMOUNT "stat"	SYSCODE_DENIED
ERASE		path			RETURN syscode		example: ERASE "fs0:file.ef"	SYSCODE_IN_USE
OPEN		ptrpath	mode		RETURN fptr		example: OPEN  "fs1:ahoj/hello.txt"	MODE_R	SYSCODE_OK	[MODE_WRITE MODE_READ MODE_CREATE]
CLOSE		fptr			RETURN syscode
WRITE		fptr	datptr	len	RETURN len
READ		fptr	datptr	len	RETURN len/EOF
SEEK		fptr	pos		RETURN syscode
IOCTL		fptr	code	optptr	RETURN syscode

OPENDIR		path	mode		RETURN dptr		example: OPENDIR fs0:myfolder/newfolder MODE_CREATE
LISTDIR		dptr	datptr	len	RETURN len
CLOSEDIR	dptr			RETURN syscode

Operace s procesy:
------------------
EXEC		path			RETURN pptr
SPAWN		fxptr	stack		RETURN pptr
SWITCH					RETURN syscode
SLEEP		timems			RETURN syscode
KILL		pptr			RETURN syscode

Operace s pamětí:
-----------------
MALLOC		size			RETURN ptr
FREE		ptr			RETURN syscode

Každý proces má
-----------------------------
Přiřazenou velikost stacku, maximální počet heap pointerů, maximální množství subprocesů (EXEC & SPAWN)
stdin a stdout buffer (kromě SPAWN, tam to sdílí s nadřazeným procesem)

Obsah souboru stat:mounts
rootname devname fsdrivername
-----------------------------
stat NULL statfs
dev NULL devfs
fs0 mem0 msefs
fs1 mmc0 fat32
fs2 NULL ramfs


