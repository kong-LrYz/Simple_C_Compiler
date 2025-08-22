#ifndef EMITTER_TMPFILE_H
#define EMITTER_TMPFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
    FILE *out;        // 最终输出（你的 fp）
    FILE *body;       // 函数体缓存（tmpfile）
    const char *func_name;
    int locals;       // sub esp, locals
    // 可选：需要保存的寄存器标志
    int save_ebx, save_esi, save_edi;

    // 统一尾声标签（为避免与其他函数冲突，用自增id拼接）
    int uid;
} FuncEmitterTF;



// 你可以用一个全局计数器确保标签唯一
static int g_func_uid = 0;

static inline void fetf_begin(FuncEmitterTF *fe, FILE *final_out,
                              const char *name, /*先占位*/ int vsize_guess) {
    memset(fe, 0, sizeof(*fe));
    fe->out       = final_out;
    fe->func_name = name;
    fe->locals    = vsize_guess;
    fe->uid       = ++g_func_uid;

    fe->body = tmpfile();
    if (!fe->body) { perror("tmpfile"); exit(1); }
}

// 把函数体的指令写入临时文件
static inline void fetf_emit(FuncEmitterTF *fe, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    vfprintf(fe->body, fmt, ap);
    va_end(ap);
}

// 结束：把序言插到最前、拷贝函数体、写统一尾声
static inline void fetf_end(FuncEmitterTF *fe) {
    // 1) 发序言（最前）
    fprintf(fe->out, "global %s\nsection .text\n%s:\n", fe->func_name, fe->func_name);
    fprintf(fe->out, "    push ebp\n");
    fprintf(fe->out, "    mov  ebp, esp\n");
    if (fe->save_ebx) fprintf(fe->out, "    push ebx\n");
    if (fe->save_esi) fprintf(fe->out, "    push esi\n");
    if (fe->save_edi) fprintf(fe->out, "    push edi\n");
    if (fe->locals > 0) fprintf(fe->out, "    sub  esp, %d\n", fe->locals);

    // 2) 拷贝函数体缓存
    rewind(fe->body);
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, fe->body)) > 0) {
        fwrite(buf, 1, n, fe->out);
    }

    // 3) 统一尾声（标签名确保唯一）
    fprintf(fe->out, ".Lret_%d:\n", fe->uid);
    if (fe->save_edi) fprintf(fe->out, "    pop  edi\n");
    if (fe->save_esi) fprintf(fe->out, "    pop  esi\n");
    if (fe->save_ebx) fprintf(fe->out, "    pop  ebx\n");
    fprintf(fe->out, "    mov  esp, ebp\n");
    fprintf(fe->out, "    pop  ebp\n");
    fprintf(fe->out, "    ret\n");

    fclose(fe->body);
}

// 在 function-definition 结束时发现真实 vsize，再设置一次
static inline void fetf_fix_locals(FuncEmitterTF *fe, int vsize_real) {
    fe->locals = vsize_real;
}

#endif // EMITTER_TMPFILE_H