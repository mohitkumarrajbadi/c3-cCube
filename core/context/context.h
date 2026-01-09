#pragma once
#include <cstdint>

namespace c3
{
    using ContextHash = uint64_t;

    enum Intent : uint8_t
    {
        INTENT_UNKNOWN = 0,
        INTENT_FACTUAL,
        INTENT_INSTRUCTIONAL,
        INTENT_EXPLANATORY,
        INTENT_CONVERSATIONAL,
        INTENT_DEBUGGING,
        INTENT_MAX
    };

    enum Domain : uint8_t
    {
        DOMAIN_GENERAL = 0,
        DOMAIN_SEARCH,
        DOMAIN_QA,
        DOMAIN_CHAT,
        DOMAIN_CODE,
        DOMAIN_AGENT,
        DOMAIN_MAX
    };

    enum Tool : uint8_t
    {
        TOOL_NONE = 0,
        TOOL_SEARCH,
        TOOL_RAG,
        TOOL_API,
        TOOL_CODE_EXEC,
        TOOL_AGENT,
        TOOL_MAX
    };

    struct ContextFeatures
    {
        uint32_t intent = 0;
        uint32_t domain = 0;
        uint32_t tool = 0;
        uint32_t retry = 0;
    };

    class ContextEncoder
    {
    public:
        static ContextHash encode(const ContextFeatures &ctx);
    };
}
