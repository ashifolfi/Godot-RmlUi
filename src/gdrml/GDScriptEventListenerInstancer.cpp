#include "GDScriptEventListenerInstancer.hpp"
#include "GDScriptEventListener.hpp"

using namespace godrml;

GDScriptEventListenerInstancer::GDScriptEventListenerInstancer()
{
}

GDScriptEventListenerInstancer::~GDScriptEventListenerInstancer()
{
}

Rml::EventListener* GDScriptEventListenerInstancer::InstanceEventListener(const Rml::String& value, Rml::Element* element)
{
	return new GDScriptEventListener(element, value);
}
