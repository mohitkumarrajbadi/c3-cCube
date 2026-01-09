import c3
print(c3)

mem = c3.Memory()
ctx = c3.Context()
ctx.intent = c3.Intent.FACTUAL
ctx.domain = c3.Domain.QA
ctx.tool = c3.Tool.SEARCH
ctx.retry = 0

print(mem.recall(ctx).prefer, mem.recall(ctx).avoid)
