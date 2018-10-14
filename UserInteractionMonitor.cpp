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
		ButtonInteraction interaction = button->ackInteraction();

		if (interaction.getClicksCount() > 0
				|| (interaction.getHoldStepsCount() > 0
						&& interaction.getHoldStepsCount()
								!= lastHoldStepsCountDelivered)) {
			lastHoldStepsCountDelivered = interaction.getHoldStepsCount();
			gnulight->interpretUserInteraction(interaction);
		}
	} else {
		noInterrupts();
		if (!button->isUserInteracting()) {
			gnulight->StopTask(this);
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
