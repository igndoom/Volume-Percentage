/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

float mod_volume;


float MaxVolume = Mod::get()->getSettingValue<float>("maximum-volume");
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
		mod_volume = PlayLayer::get()->getCurrentPercent();
		if(mod_volume > MaxVolume){
			mod_volume = MaxVolume;
		};
		// log::info("{}", mod_volume);
		FMODAudioEngine::get()->setBackgroundMusicVolume(mod_volume / 100);
		if(EditSFX) FMODAudioEngine::get()->setEffectsVolume(mod_volume / 100);
		
	}
	
};