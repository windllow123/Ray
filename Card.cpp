#include "Card.h"

Card::Card(CardType t) : type(t) {
    switch (type) {
        case CardType::SHA: name = "杀"; break;
        case CardType::SHAN: name = "闪"; break;
        case CardType::TAO: name = "桃"; break;
    }
}

std::string Card::getName() const {
    return name;
}