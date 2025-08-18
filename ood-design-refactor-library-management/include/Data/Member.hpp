#pragma once
#include <string>

class Member {
public:
    Member() = default;
    Member(std::string name, std::string memberId) : name_(std::move(name)), memberId_(std::move(memberId)) {}

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    const std::string& getMemberId() const { return memberId_; }
    void setMemberId(const std::string& memberId) { memberId_ = memberId; }

    // Equality based on memberId (mirrors typical identity semantics)
    bool operator==(const Member& other) const { return memberId_ == other.memberId_; }

private:
    std::string name_;
    std::string memberId_;
};

// Hash for Member so it can be used as a key in unordered_map
namespace std {
template<> struct hash<Member> {
    size_t operator()(const Member& m) const noexcept {
        return std::hash<std::string>()(m.getMemberId());
    }
};
}
