#ifndef COMMAND
#define COMMAND

/*******************************************************************************
 * Command
 * This file contains declarations for parsing command input and issuing signals
 * to the FCB.
 *
 * When a command is input into the terminal, the STM microcontroller should
 * respond as soon as possible. This can be achieved by generating an interrupt
 * when the signal is received. Perhaps in the future this can be expanded to
 * nonessential commands, where the microcontroller doesn't have to process the
 * command immediately.
 * The command structure is as follows (tentative).
 * <cmd_name> <flags> <params>
 ******************************************************************************/

enum CommandTypes {
    LAUNCH,
    ABORT
};



#endif