/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;


float MaxVolume = Mod::get()->getSettingValue<double>("maximum-volume");
bool EditSFX = Mod::get()->getSettingValue<bool>("edit-sfx");

$execute {
    listenForSettingChanges("maximum-volume", [](float value) {
        MaxVolume = value;
    });
    listenForSettingChanges("edit-sfx", [](bool value) {
        EditSFX = value;
    });
}

#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>

class $modify(PlayLayer) {


	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		if (m_isPlatformer) return;
		float mod_volume = getCurrentPercent();
		if(mod_volume > MaxVolume){
			mod_volume = MaxVolume;
		};
		// log::info("{}", mod_volume);
		FMODAudioEngine* engine = FMODAudioEngine::get();
		if(engine->m_backgroundMusicChannel) engine->m_backgroundMusicChannel->setVolume(mod_volume / 100);
		if(EditSFX && engine->m_globalChannel) engine->m_globalChannel->setVolume(mod_volume / 100);
		
	}
	
	void onExit() {
		PlayLayer::onExit();
		if (m_isPlatformer) return;
		FMODAudioEngine* engine = FMODAudioEngine::get();
		if(engine->m_backgroundMusicChannel) engine->m_backgroundMusicChannel->setVolume(engine->m_musicVolume);
		if(EditSFX && engine->m_globalChannel) engine->m_globalChannel->setVolume(engine->m_sfxVolume);
	}
};