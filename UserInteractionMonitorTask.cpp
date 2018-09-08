#include "UserInteractionMonitorTask.h"

#include "Button.h"
#include "Gnulight.h"
#include "GnulightMode.h"

UserInteractionMonitorTask::UserInteractionMonitorTask(uint32_t timeInterval,
		Gnulight* gnulight) :
		Task(timeInterval), HostSystemAware(gnulight) {
	trace("Inst. UIMT");
}

void UserInteractionMonitorTask::OnUpdate(uint32_t deltaTime) {
	if (pSystem->button.isUserInteracting()) {
		ButtonInteraction interaction = pSystem->button.ackInteraction();

		if (interaction.getClicksCount() > 0
				|| (interaction.getHoldStepsCount() > 0
						&& interaction.getHoldStepsCount()
								!= lastHoldStepsCountDelivered)) {
			debug(
					"Btn interaction. " + interaction.getClicksCount() + " clicks, " + interaction.getHoldStepsCount() + " hold steps");
			lastHoldStepsCountDelivered = interaction.getHoldStepsCount();
			pSystem->interpretUserInteraction(interaction);
		}
	} else {
		noInterrupts();
		if (!pSystem->button.isUserInteracting()) {
			pSystem->StopTask(this);
		}
		interrupts();
	}
}

bool UserInteractionMonitorTask::OnStart() {
	trace("UIMT::OnStart");
	return true;
}

void UserInteractionMonitorTask::OnStop() {
	trace("UIMT::OnStop");
}
