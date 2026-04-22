#pragma once
#include <string>
#include <cstdlib>
#include <ctime>

struct Skill {
    std::string name;
    std::string desc;

    static Skill getRandomSkill() {
        int r = rand() % 6;
        switch (r) {
            case 0: return {"铁骑", "当敌方出闪抵消杀的攻击时，杀有50%的概率强制命中"};
            case 1: return {"咆哮", "每回合能额外出一次杀"};
            case 2: return {"苦肉", "主动技能：扣除自己一点血量，获得两张牌"};
            case 3: return {"克己", "当回合中没有出过杀的时候，可以跳过本回合的弃牌阶段"};
            case 4: return {"奸雄", "当你受到伤害时，你可以获得造成伤害的牌"};
            case 5: return {"龙胆", "你可以将杀当闪，闪当杀使用"};
            default: return {"无", "无效果"};
        }
    }
};