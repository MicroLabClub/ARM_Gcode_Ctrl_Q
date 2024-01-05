#ifndef COMDATATYPES_H
#define COMDATATYPES_H

#include "commdefines.h"
#include "pdudatatypes.h"
#include "tp.h"
#include "comsignal.h"
#include <QSharedPointer>
#include <QObject>

/**
 * @namespace Communication
 * @brief Contain communication data types.
 */
namespace Communication {

/**
 * @brief TpInterfaceType
 */
typedef QSharedPointer<Communication::Tp>& TpInterfaceType;

/**
 * @brief The ComIPduSignalProcessingModeType enum
 */
enum ComIPduSignalProcessingModeType {
    eComSigProcImediate,
    eComSigProcDeferred,
} ;

/**
 * @brief The ComTxTriggerStatusType enum
 */
enum ComTxTriggerStatusType {
    eComTxTriggered,
    eComTxNotTriggered,
};

/**
 * @brief The ComIPduTransferPropertyType enum
 */
enum ComIPduTransferPropertyType {
    eComTransferPending,
    eComTransferTriggered,
    eComTransferTriggeredWithoutRepetition,
    eComTransferTriggeredOnChangeWithoutRepetition,
    eComTransferTriggeredOnChange,
};

/**
 * @brief The ComIPduDirectionType enum
 */
enum ComIPduDirectionType {
    eComDirSend,
    eComDirReceive,
    eComDirNone,
} ;

/**
 * @brief The ComIPduTxClearUpdateBitType enum
 */
enum ComIPduTxClearUpdateBitType {
    eComUpdateOnConfirmation,
    eComUpdateOnTransmit,
    eComUpdateNone,
};

/**
 * @brief The ComIPduTxModeModeType enum
 */
enum ComIPduTxModeModeType {
    eComTxModeDirect,
    eComTxModePeriodic,
    eComTxModeNone,
};

/**
 * @brief The ComIPduStateType struct
 */
struct ComIPduStateType {
    bool locked;
};

/**
 * @brief The ComIPduTxTimerType struct
 */
struct ComIPduTxTimerType {
    uint32_t comIPduTxModeTimePeriodTimer;
    uint8_t  comIPduTxNumberOfRepetitionsLeft;
};

/**
 * @brief The ComIPduTxModeType struct
 */
struct ComIPduTxModeType {
    /**
     * @brief Transmission mode for this IPdu.
     */
    ComIPduTxModeModeType comIPduTxModeMode;

    /**
     * @brief Period of cyclic transmission.
     */
    uint32_t comIPduTxModeTimePeriodFactor;
};

/**
 * @brief The ComIPduTxType struct
 */
struct ComIPduTxType {
    /**
     * @brief COM will fill unused areas within an IPdu with this bit patter.
     */
    uint8_t comIPduTxUnusedAreasDefault;

    /**
     * @brief Transmission modes for the IPdu.
     */
    ComIPduTxModeType comIPduTxMode;

    /**
     * @brief The TX IPDU timers.
     */
    ComIPduTxTimerType comIPduTxTimers;
};

/**
 * @brief The ComIPduType struct
 */
struct ComIPduType {
    /**
     * @brief The outgoing PDU id. For polite PDU id handling.
     */
    PduIdType comIPduOutgoingId;

    /**
     * @brief The direction of the IPDU. Receive or Send.
     */
    ComIPduDirectionType comIPduDirection;

    /**
     * @brief Size of the IPDU in bytes.
     *        Range 0 - COM_MAX_IPDU_BUFFER_SIZE.
     */
    uint8_t comIPduSize;

    /**
     * @brief An IPDU started indication.
     */
    bool comIpduStarted;

    /**
     * @brief Container of transmission related parameters.
     */
    ComIPduTxType comIPduTx;

    /**
     * @brief Actual I-PDU state.
     */
    ComIPduStateType comIpduState;

    /**
     * @brief I-PDU's signal handle.
     */
    ComSignal * comSignalHandle;

    /**
     * @brief Marks if this I-PDU is connected to notification signal or not.uses an update bit.
     */
    bool comSignalNotificationConnected;

    /**
     * @brief Marks if this I-PDU is connected to notification signal or not.uses an update bit.
     */
    bool comSignalNotificationErrorConnected;

    /**
     * @brief Actual I-PDU data storage
     */
    uint8_t comIPduBuffer[COM_MAX_IPDU_BUFFER_SIZE];
};

} // end namespace

#endif // COMDATATYPES_H
