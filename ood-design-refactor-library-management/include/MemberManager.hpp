#pragma once
#include <vector>
#include <string>
#include "Member.hpp"

class MemberManager {
public:
    MemberManager() = default;
    MemberManager(const std::vector<Member>& members) : members(members) {}

    void RegisterMember(const Member& member) {
        members.push_back(member);
    };
    void RemoveMember(const std::string& memberId){
        auto it = std::remove_if(members.begin(), members.end(),
            [&](const Member& m){ return m.getMemberId() == memberId; });
        members.erase(it, members.end());
    };
    void UpdateMember(const std::string& memberId, const Member& updatedMember){
        auto it = std::find_if(members.begin(), members.end(),
            [&](const Member& m){ return m.getMemberId() == memberId; });
        if (it != members.end()) {
            it->setName(updatedMember.getName());
            it->setMemberId(updatedMember.getMemberId());
        }
    }

    Member* FindMember(const std::string& memberId){
        auto it = std::find_if(members.begin(), members.end(),
            [&](const Member& m){ return m.getMemberId() == memberId; });
        return (it != members.end()) ? &(*it) : nullptr;
    };

    

private:
    std::vector<Member> members;
};
