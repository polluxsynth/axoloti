/* Copyright (C) 2007 Jean-Marc Valin, 2016 Ricard Wanderlof
      
   File: os_support.h
   OS abstraction layer for speexdsp lib for Axoloti enviornment.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OS_SUPPORT_CUSTOM_H
#define OS_SUPPORT_CUSTOM_H

/* The USB printout function in Axoloti. */
extern void LogTextMessage(const char* format, ...);

#if 0
/** Speex wrapper for calloc. To do your own dynamic allocation, all you need to do is replace this function, speex_realloc and speex_free 
    NOTE: speex_alloc needs to CLEAR THE MEMORY */
#ifndef OVERRIDE_SPEEX_ALLOC
static inline void *speex_alloc (int size)
{
   /* WARNING: this is not equivalent to malloc(). If you want to use malloc() 
      or your own allocator, YOU NEED TO CLEAR THE MEMORY ALLOCATED. Otherwise
      you will experience strange bugs */
   return calloc(size,1);
}
#endif

/** Same as speex_alloc, except that the area is only needed inside a Speex call (might cause problem with wideband though) */
#ifndef OVERRIDE_SPEEX_ALLOC_SCRATCH
static inline void *speex_alloc_scratch (int size)
{
   /* Scratch space doesn't need to be cleared */
   return calloc(size,1);
}
#endif

/** Speex wrapper for realloc. To do your own dynamic allocation, all you need to do is replace this function, speex_alloc and speex_free */
#ifndef OVERRIDE_SPEEX_REALLOC
static inline void *speex_realloc (void *ptr, int size)
{
   return realloc(ptr, size);
}
#endif

/** Speex wrapper for calloc. To do your own dynamic allocation, all you need to do is replace this function, speex_realloc and speex_alloc */
#ifndef OVERRIDE_SPEEX_FREE
static inline void speex_free (void *ptr)
{
   free(ptr);
}
#endif

/** Same as speex_free, except that the area is only needed inside a Speex call (might cause problem with wideband though) */
#ifndef OVERRIDE_SPEEX_FREE_SCRATCH
static inline void speex_free_scratch (void *ptr)
{
   free(ptr);
}
#endif

/** Copy n elements from src to dst. The 0* term provides compile-time type checking  */
#ifndef OVERRIDE_SPEEX_COPY
#define SPEEX_COPY(dst, src, n) (memcpy((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Copy n elements from src to dst, allowing overlapping regions. The 0* term
    provides compile-time type checking */
#ifndef OVERRIDE_SPEEX_MOVE
#define SPEEX_MOVE(dst, src, n) (memmove((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** For n elements worth of memory, set every byte to the value of c, starting at address dst */
#ifndef OVERRIDE_SPEEX_MEMSET
#define SPEEX_MEMSET(dst, c, n) (memset((dst), (c), (n)*sizeof(*(dst))))
#endif
#endif


#define OVERRIDE_SPEEX_FATAL
static inline void _speex_fatal(const char *str, const char *file, int line)
{
   LogTextMessage("Fatal (internal) error in %s, line %d: %s\n", file, line, str);
   while (1) /* hang */
     ;
}

#define OVERRIDE_SPEEX_WARNING
static inline void speex_warning(const char *str)
{
#ifndef DISABLE_WARNINGS
   LogTextMessage("warning: %s\n", str);
#endif
}

#define OVERRIDE_SPEEX_WARNING_INT
static inline void speex_warning_int(const char *str, int val)
{
#ifndef DISABLE_WARNINGS
   LogTextMessage("warning: %s %d\n", str, val);
#endif
}

#define OVERRIDE_SPEEX_NOTIFY
static inline void speex_notify(const char *str)
{
#ifndef DISABLE_NOTIFICATIONS
   LogTextMessage("notification: %s\n", str);
#endif
}

#define OVERRIDE_SPEEX_PUTC
/** Speex wrapper for putc */
static inline void _speex_putc(int ch, void *file)
{
   FILE *f = (FILE *)file;
   LogTextMessage("0x%02x ", ch);
}

#ifndef RELEASE
static inline void print_vec(float *vec, int len, char *name)
{
   int i;
   LogTextMessage("%s ", name);
   for (i=0;i<len;i++)
      LogTextMessage(" %f", vec[i]);
   LogTextMessage("\n");
}
#endif

#endif /* OS_SUPPORT_CUSTOM_H */

