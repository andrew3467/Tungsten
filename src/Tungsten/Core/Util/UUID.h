//
// Created by Andrew Graser on 8/19/2026.
//


#pragma once

namespace Tungsten {
    class UUID {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const {return mUUID;}

    private:
        uint64_t mUUID;
    };
}

namespace std {
    template<>
    struct hash<Tungsten::UUID> {
        std::size_t operator()(const Tungsten::UUID& uuid) const {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}
