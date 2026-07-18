#include "LevelShowcaseLayer.hpp"

using namespace geode::prelude;

LevelShowcaseLayer* LevelShowcaseLayer::create() {
    auto ret = new LevelShowcaseLayer();
    // 400x280 gives it a slightly wider, clean classic canvas for listing runs
    if (ret && ret->initAnchored(400.f, 280.f, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool LevelShowcaseLayer::setup() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setTitle("Level Showcase");

    // Grab our custom layer size for internal positioning calculations
    auto layerSize = m_mainLayer->getContentSize();

    // 1. Everyplay Style Header/Status Label
    auto statusLabel = CCLabelBMFont::create("Everyplay Emulation Active", "chatFont.fnt");
    statusLabel->setScale(0.6f);
    statusLabel->setColor({ 0, 255, 0 }); // Vibrant green status accent
    statusLabel->setPosition({ layerSize.width / 2, layerSize.height - 45.f });
    m_mainLayer->addChild(statusLabel);

    // 2. Showcase Meta Info Display (Simulating an active clip or feed)
    auto infoBG = CCScale9Sprite::create("square02b_001.png");
    infoBG->setContentSize({ 340.f, 120.f });
    infoBG->setOpacity(100);
    infoBG->setPosition({ layerSize.width / 2, layerSize.height / 2 + 5.f });
    m_mainLayer->addChild(infoBG);

    // Add mock text showing video clip data inside the box
    auto feedText = CCLabelBMFont::create("No local showcase clip saved.\nRecord a macro or play a level to generate a run feed.", "goldFont.fnt");
    feedText->setScale(0.5f);
    feedText->setAlignment(kCCTextAlignmentCenter);
    feedText->setPosition({ infoBG->getContentSize().width / 2, infoBG->getContentSize().height / 2 });
    infoBG->addChild(feedText);

    // 3. Action Menu Buttons Setup
    auto menu = CCMenu::create();
    menu->setPosition({ 0, 0 });
    m_mainLayer->addChild(menu);

    // Button A: Clear Feed / Reset Data
    auto resetBtnSprite = ButtonSprite::create("Reset Feed", "goldFont.fnt", "GJ_button_06.png");
    resetBtnSprite->setScale(0.8f);
    auto resetBtn = CCMenuItemSpriteExtra::create(
        resetBtnSprite, 
        this, 
        menu_selector(LevelShowcaseLayer::onResetFeed)
    );
    resetBtn->setPosition({ layerSize.width / 2 - 90.f, 40.f });
    menu->addChild(resetBtn);

    // Button B: Mock Upload/Share Option
    auto shareBtnSprite = ButtonSprite::create("Upload Clip", "goldFont.fnt", "GJ_button_01.png");
    shareBtnSprite->setScale(0.8f);
    auto shareBtn = CCMenuItemSpriteExtra::create(
        shareBtnSprite, 
        this, 
        menu_selector(LevelShowcaseLayer::onShareShowcase)
    );
    shareBtn->setPosition({ layerSize.width / 2 + 90.f, 40.f });
    menu->addChild(shareBtn);

    return true;
}

void LevelShowcaseLayer::onShareShowcase(CCObject* sender) {
    FLAlertLayer::create(
        "Showcase Server", 
        "Everyplay feature upload completed successfully!\nClip processing finalized.", 
        "OK"
    )->show();
}

void LevelShowcaseLayer::onResetFeed(CCObject* sender) {
    FLAlertLayer::create(
        "Showcase Settings", 
        "Local level showcase queue has been cleared.", 
        "OK"
    )->show();
}