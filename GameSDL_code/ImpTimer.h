#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer {
public:
	ImpTimer();
	~ImpTimer();
	void start();
	void stop();
	void paused();
	void unpaused();
	int get_tick();
	bool is_started();
	bool is_paused();
private:
	bool is_started_;
	bool is_paused_;

	int start_tick;
	int paused_tick;
};

#endif // !IMP_TIMER_H_
