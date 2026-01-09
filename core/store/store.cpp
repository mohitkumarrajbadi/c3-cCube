#include "store.h"

namespace c3 {

    std::vector<CausalRule>& MemoryStore::get(ContextHash context)
    {
        // Creates entry if it does not exist (update path)
        return data_[context];
    }

    const std::vector<CausalRule>& MemoryStore::get(ContextHash context) const
    {
        // Read-only access (recall path)
        static const std::vector<CausalRule> empty;

        auto it = data_.find(context);
        return (it != data_.end()) ? it->second : empty;
    }

    bool MemoryStore::exists(ContextHash context) const
    {
        return data_.find(context) != data_.end();
    }

    size_t MemoryStore::size() const
    {
        return data_.size();
    }

    void MemoryStore::clear()
    {
        data_.clear();
    }

}
