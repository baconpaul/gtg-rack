#include "gtgComponents.hpp"


// themed button (switch)
void ThemedSvgSwitch::addFrameAll(std::shared_ptr<Svg> svg) {
    framesAll.push_back(svg);
	if (framesAll.size() == 1) {
		addFrame(framesAll[0]);
	}
}

void ThemedSvgSwitch::step() {
    if(theme != NULL && *theme != old_theme) {
        if ((*theme) == 0 || framesAll.size() < 2) {
			frames[0]=framesAll[0];
		}
		else {
			frames[0]=framesAll[1];
		}
        old_theme = *theme;
		onChange(*(new event::Change()));
		fb->dirty = true;
	}
	SvgSwitch::step();
}

// themed knob
void ThemedSvgKnob::addFrameAll(std::shared_ptr<Svg> svg) {
    framesAll.push_back(svg);
	if (framesAll.size() == 1) {
		setSvg(svg);
	}
}

void ThemedSvgKnob::step() {
    if(theme != NULL && *theme != old_theme) {
        if ((*theme) == 0) {
			setSvg(framesAll[0]);
		}
		else {
			setSvg(framesAll[1]);
		}
        old_theme = *theme;
		fb->dirty = true;
    }
	SvgKnob::step();
}

// themed snap knob
void ThemedRoundBlackSnapKnob::addFrameAll(std::shared_ptr<Svg> svg) {
    framesAll.push_back(svg);
	if (framesAll.size() == 1) {
		setSvg(svg);
	}
}

void ThemedRoundBlackSnapKnob::step() {
    if(theme != NULL && *theme != old_theme) {
        if ((*theme) == 0) {
			setSvg(framesAll[0]);
		}
		else {
			setSvg(framesAll[1]);
		}
        old_theme = *theme;
		fb->dirty = true;
    }
	SvgKnob::step();
}

// themed port
void ThemedSvgPort::addFrame(std::shared_ptr<Svg> svg) {
	frames.push_back(svg);
	if(frames.size() == 1) {
		SvgPort::setSvg(svg);
	}
}

void ThemedSvgPort::step() {
	if(theme != NULL && *theme != old_theme) {
		sw->setSvg(frames[*theme]);
		old_theme = *theme;
		fb->dirty = true;
	}
	PortWidget::step();
}

// themed screw
void ThemedSvgScrew::addFrame(std::shared_ptr<Svg> svg) {
	frames.push_back(svg);
	if(frames.size() == 1) {
		SvgScrew::setSvg(svg);
	}
}

void ThemedSvgScrew::step() {
	if(theme != NULL && *theme != old_theme) {
		sw->setSvg(frames[*theme]);
		old_theme = *theme;
		fb->dirty = true;
	}
	SvgScrew::step();
}

// save default theme
void saveDefaultTheme(int theme) {
	json_t *settingsJ = json_object();
	json_object_set_new(settingsJ, "default_theme", json_integer(theme));
	std::string settingsFilename = asset::user("GlueTheGiant.json");
	FILE *file = fopen(settingsFilename.c_str(), "w");
	if (file) {
		json_dumpf(settingsJ, file, JSON_INDENT(2) | JSON_REAL_PRECISION(9));
		fclose(file);
	}
	json_decref(settingsJ);
}

// load default theme
int loadDefaultTheme() {
	int theme = 0;
	std::string settingsFilename = asset::user("GlueTheGiant.json");
	FILE *file = fopen(settingsFilename.c_str(), "r");
	if (!file) {   // file does not exist
		return theme;
	}
	json_error_t error;
	json_t *settingsJ = json_loadf(file, 0, &error);
	if (!settingsJ) {   // file invalid
		fclose(file);
		return theme;
	}
	json_t *default_themeJ = json_object_get(settingsJ, "default_theme");
	if (default_themeJ)
		theme = json_integer_value(default_themeJ);
	fclose(file);

	json_decref(settingsJ);
	return theme;
}
