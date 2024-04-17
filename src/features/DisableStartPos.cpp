#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify (DisableStartPosLayer, EditorUI)
{
    void onDisable(CCObject*)
    {
        CCArrayExt<GameObject*> objects = this->m_editorLayer->m_objects;

        for (auto obj : objects)
        {
            if (auto startPos = typeinfo_cast<StartPosObject*>(obj))
            {                
                startPos->m_startSettings->m_disableStartPos = true;
            }
        }

        if (!getChildOfType<Notification>(CCScene::get(), 0))
            Notification::create("Disabled all Start Positions", CCSprite::createWithSpriteFrameName("edit_eStartPosBtn_001.png"), 0.3f)->show();
    }

    bool init(LevelEditorLayer* editor)
    {
        if (!EditorUI::init(editor))
            return false;

        if (auto menu = m_deleteMenu->getChildByID("delete-button-menu"))
        {
            auto disableSpr = CCSprite::create();
            auto disableLbl = CCSprite::createWithSpriteFrameName("be-disable-btn.png"_spr);
            disableSpr->addChildAtPosition(disableLbl, Anchor::Center, ccp(0, 8));

            auto startPosIcon = CCSprite::createWithSpriteFrameName("edit_eStartPosBtn_001.png");
            startPosIcon->setScale(0.7f);
            disableSpr->addChildAtPosition(startPosIcon, Anchor::Center, ccp(0, -8));

            auto btnSpr = ButtonSprite::create(disableSpr, 32, 0, 32.0f, 1.0f, true, "GJ_button_04.png", true);
            auto btn = CCMenuItemSpriteExtra::create(btnSpr, this, menu_selector(DisableStartPosLayer::onDisable));

            menu->addChild(btn);
            menu->updateLayout(); // probably unnecessary but just in case
        }

        return true;
    }
};