#ifndef TV_H_
#define TV_H_

class Tv
{
 public:
	friend class Remote;
	enum {Off ,On};
	enum {MinVal , MaxVal = 20};
	enum {Antenna , Cable };
	enum {TV , VCR};
	
 Tv(int s = Off , int mc = 100): state(s) , volume(5) , maxchannel(mc) , channel(2) , mode (Cable) ,input(TV){}
	void onoff(){state = (state == On) ? Off : On;}
	bool ison()const { return state == On ;}
	bool volup();
	bool voldown();
	void set_mode() {mode = (mode == Antenna ) ? Cable : Antenna;}
	void set_input() {input = (input == TV )? VCR : TV;}
	void setting() const;
 private:
	int state , volume , maxchannel , channel , mode , input;
};

class Remote
{
 private:
	int mode;
 public:
 Remote(int m = Tv :: TV) : mode(m){}
	int volup (const Tv & t) {t.volume;}
	int voldown(const Tv & t) {t.state;}
	//  int onoff(Tv & t) {return t.voldown;}
	//	int channel(Tv & t){t.channel;}
	//	int 
};
#endif
