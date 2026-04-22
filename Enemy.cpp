#include "Enemy.h"
#include <iostream>
#include <windows.h>

Enemy::Enemy() {
    deck.initEnemyDeck();
    startDraw();
}

void Enemy::startDraw() {
    for (int i = 0; i < 2; i++) hand.push_back(deck.drawCard());
}

void Enemy::drawOne() {
    hand.push_back(deck.drawCard());
}

void Enemy::showStatus() {
    std::cout << "敌人血量：" << hp << "/" << max_hp << " | 敌人手牌：" << hand.size() << "张 | 可抵挡杀次数：" << shan_defense << "\n";
}

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
    std::cout << "敌人受到" << dmg << "点伤害！\n";
    Sleep(1000);
}

// 新闪机制：抵消玩家的防御次数
void Enemy::attack(Player& p) {
    std::cout << "\n敌人对你使用【杀】！\n";
    Sleep(1000);
    if (p.shan_defense > 0) {
        p.shan_defense--;
        std::cout << "你用闪抵挡了这次攻击！\n";
        Sleep(1000);
    } else {
        p.hp -= 1;
        std::cout << "你受到1点伤害！\n";
        Sleep(1000);
        if (p.hasSkill("奸雄")) {
            Card gained = deck.drawCard(); // 简化：获得一张牌
            p.hand.push_back(gained);
            std::cout << "奸雄发动！你获得一张牌：【" << gained.getName() << "】\n";
            Sleep(1000);
        }
    }
}

void Enemy::discardExcessCards() {
    std::cout << "\n敌人弃牌阶段：\n";
    Sleep(500);
    if (hand.size() <= static_cast<size_t>(hp)) {
        std::cout << "手牌数量未超过血量上限，无需弃牌。\n";
        Sleep(500);
        return;
    }
    while (hand.size() > static_cast<size_t>(hp)) {
        Card c = hand.back();
        deck.discardCard(c);
        hand.pop_back();
        std::cout << "敌人弃掉一张牌：【" << c.getName() << "】\n";
        Sleep(500);
    }
}

void Enemy::playCards() {
    std::cout << "\n敌人出牌阶段：\n";
    Sleep(500);
    for (auto it = hand.begin(); it != hand.end(); ) {
        if (it->type == CardType::SHAN) {
            shan_defense++;
            deck.discardCard(*it);
            it = hand.erase(it);
            std::cout << "敌人使用【闪】，获得1次攻击抵挡！\n";
            Sleep(1000);
        } else {
            ++it;
        }
    }
    if (shan_defense == 0) {
        std::cout << "敌人没有出闪。\n";
        Sleep(500);
    }
}