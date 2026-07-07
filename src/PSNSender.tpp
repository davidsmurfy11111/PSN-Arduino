template<uint8_t MaxTrackers>
PSNSender<MaxTrackers>::PSNSender(EthernetUDP& udp)
    : m_udp(udp),
      m_port(psn::DefaultPort),
      m_writer(m_packet, sizeof(m_packet)),
      m_infoRequired(true)
{
    m_systemName[0] = '\0';
}
