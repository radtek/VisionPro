#ifndef MBASICSETTINGS_H
#define MBASICSETTINGS_H

#include <string>
#include <vector>

class MBasicSettings{
public:
    explicit MBasicSettings();
	~MBasicSettings();

    MBasicSettings(const MBasicSettings& rhs) ;
	MBasicSettings& operator=(const MBasicSettings& rhs);

    MBasicSettings(MBasicSettings&& rhs)=delete;
    MBasicSettings& operator=(MBasicSettings&& rhs)=delete;

    void set_camera_type(const std::string &camera_type);
    std::string get_camera_type() const;

    void set_camera_count(const int &camera_count);
    int get_camera_count() const;

	void set_camera_exposure(const std::string &camera_exposure);
	std::string get_camera_exposure() const;

	void set_camera_trigger(const std::string &camera_trigger);
	std::string get_camera_trigger()const;

    void set_communication_type(const std::string &communication_type);
    std::string get_communication_type() const;

    void set_communication_count(const int &communication_count);
    int get_communication_count() const;

	void set_tcp_ip(const std::string &ip);
	std::string get_tcp_ip()const;

	void set_tcp_port(const std::string &port);
	std::string get_tcp_port();

	void set_serial_port_number(const std::string &serial_port_number);
	std::string get_serial_port_number() const;

	void set_baud_rate(const std::string &baud_rate);
	std::string get_baud_rate() const;

	void set_parity_bits(const std::string & parity_bits);
	std::string get_parity_bits() const;

	void set_data_bits(const std::string &data_bits);
	std::string get_data_bits() const;

	void set_stop_bits(const std::string &stop_bits);
	std::string get_stop_bits() const;
private:
    std::string camera_type_;
    int camera_count_;
	std::string camera_exposure_;
	std::string camera_trigger_;
    std::string communication_type_;
    int communication_count_;
	std::string tcp_ip_;
	std::string tcp_port_;
	std::string serial_port_number_;
	std::string baud_rate_;
	std::string parity_bits_;
	std::string data_bits_;
	std::string stop_bits_;
};

#endif // MBASICSETTINGS_H
