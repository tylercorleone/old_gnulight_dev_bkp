#include "UserInteractionMonitor.h"

#include "Button.h"
#include "Gnulight.h"
#include "GnulightMode.h"

UserInteractionMonitor::UserInteractionMonitor(uint32_t timeInterval,
		Button* button, Gnulight* gnulight) :
		Task(timeInterval), button(button), gnulight(gnulight) {
	trace("Inst. UIM");
}

void UserInteractionMonitor::OnUpdate(uint32_t deltaTime) {
	if (button->isUserInteracting()) {

		/*
		 * User is interacting. Stay awake to intercept holds!
		 */
		ButtonInteraction interaction = button->ackInteraction();

		if (interaction.getClicksCount() > 0 || interaction.getHoldStepsCount() > 0) {
			
			/*
			 * We have a complete interaction
			 */
			gnulight->interpretUserInteraction(interaction);
		}
	} else {

		/*
		 * No interaction. No hold to intercept.
		 */
		noInterrupts();
		if (!button->isUserInteracting()) {

			/*
			 * Double check
			 */
			gnulight->StopTask(this);
			button->reset();
		}
		interrupts();
	}
}

bool UserInteractionMonitor::OnStart() {
	trace("UIM::OnStart");
	return true;
}

void UserInteractionMonitor::OnStop() {
	trace("UIM::OnStop");
}
