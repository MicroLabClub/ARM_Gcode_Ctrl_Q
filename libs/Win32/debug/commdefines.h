#ifndef COMMDEFINES_H
#define COMMDEFINES_H

#define COM_MAX_IPDU_BUFFER_SIZE            220U
#define COM_MAX_NOF_IPDUS                   20U
#define COM_IPDU_HANDLE_CYCLE_TIMEOUT       1UL   // 100 milliseconds cycle processing
#define COM_IPDU_SIGNAL_INVALID_HANDLE      0xFFFFU // Invalid handle value

#define COM_SERIALTP_SERVER_ADDR            0x01U
#define COM_SERIALTP_CLIENT_ADDR            0x80U
#define COM_SERIALTP_TX_LPDU_SIZE           230U
#define COM_SERIALTP_RX_LPDU_SIZE           1U
#define COM_SERIALTP_PCI_CRC_INIT           (uint8_t)0xFFU
#define COM_SERIALTP_PCI_STX_1              (uint8_t)0x55U
#define COM_SERIALTP_PCI_STX_2              (uint8_t)0xAAU
#define COM_SERIALTP_PCI_ETX_1              (uint8_t)0x32U
#define COM_SERIALTP_PCI_ETX_2              (uint8_t)0xAAU

#endif // COMMDEFINES_H
