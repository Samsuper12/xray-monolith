#pragma once

struct MotionID
{
private:
	typedef const MotionID*(MotionID::*unspecified_bool_type)() const;
public:
	union
	{
		struct
		{
			u16 idx:16; //14
			u16 slot:16; //2
		};

		//.		u16			val;
		u32 val;
	};

public:
	MotionID() { invalidate(); }
	MotionID(u16 motion_slot, u16 motion_idx) { set(motion_slot, motion_idx); }
	inline bool operator==(const MotionID& tgt) const { return tgt.val == val; }
	inline bool operator!=(const MotionID& tgt) const { return tgt.val != val; }
	inline bool operator<(const MotionID& tgt) const { return val < tgt.val; }
	inline bool operator!() const { return !valid(); }
	inline void set(u16 motion_slot, u16 motion_idx)
	{
		slot = motion_slot;
		idx = motion_idx;
	}

	inline void invalidate() { val = u16(-1); }
	inline bool valid() const { return val != u16(-1); }
	const MotionID* get() const { return this; };
	inline operator unspecified_bool_type() const
	{
		if (valid()) return &MotionID::get;
		else return 0;
		//		return(!valid()?0:&MotionID::get);
	}
};
