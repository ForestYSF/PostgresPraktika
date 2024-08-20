# Компилятор и флаги
CC = cl
CFLAGS = /I"C:\Program Files\PostgreSQL\16\include" \
         /I"C:\Program Files\PostgreSQL\16\include\server" \
         /I"C:\Program Files\PostgreSQL\16\include\server\port\win32" \
         /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\shared" \
         /I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.26100.0\um" \
         /Wall /DWIN32 /D_WINDOWS /D_USRDLL /D_WINDLL /MD

LDFLAGS = /link /DLL /OUT:temp_conv.dll /LIBPATH:"C:\Program Files\PostgreSQL\16\lib" \
          /LIBPATH:"C:\Program Files\PostgreSQL\16\lib\pgport" \
          /LIBPATH:"C:\Program Files\PostgreSQL\16\lib\pgcommon" \
          libpq.lib libpgport.lib libpgcommon.lib

# Цели сборки
all: temp_conv.dll

# Правило для создания DLL
temp_conv.dll: temp_conv.obj
	$(CC) $(LDFLAGS) temp_conv.obj

# Правило для создания объектных файлов
temp_conv.obj: temp_conv.c
	$(CC) $(CFLAGS) /c temp_conv.c

# Очистка промежуточных файлов
clean:
	del temp_conv.obj temp_conv.dll
