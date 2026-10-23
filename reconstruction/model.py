"""New reconstruction, 2026-10-23. Demo inputs are synthetic, not historical results."""
class Irrigation:
    def __init__(self, start=30, stop=55, max_seconds=20):
        if not 0 <= start < stop <= 100 or max_seconds <= 0: raise ValueError('Invalid settings')
        self.start, self.stop, self.maximum = start, stop, max_seconds
        self.on, self.since, self.fault = False, 0, False
    def step(self, moisture, now, water_available=True):
        if moisture is None or not 0 <= moisture <= 100 or not water_available:
            self.on = False
            self.fault = True
        elif self.fault: self.on = False
        elif self.on and now-self.since >= self.maximum:
            self.on, self.fault = False, True
        elif self.on and moisture >= self.stop: self.on = False
        elif not self.on and moisture <= self.start:
            self.on, self.since = True, now
        return self.on
    def reset(self): self.on, self.fault = False, False
def demo():
    c=Irrigation()
    assert c.step(20,0) and c.step(40,1)
    assert not c.step(60,2)
    assert c.step(20,3)
    assert not c.step(20,24) and c.fault
    return {'timeout_latched':c.fault,'pump_on':c.on}

if __name__ == "__main__":
    import json
    print(json.dumps(demo(), indent=2))
