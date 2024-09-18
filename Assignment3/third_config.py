import m5
from m5.objects import *

#========================================#
# below are from gem5's documentation

class L1Cache(Cache):
    assoc = 4
    tag_latency = 3
    data_latency = 3
    response_latency = 3
    mshrs = 8
    tgts_per_mshr = 16
    def __init__(self, size):
        super().__init__()
        self.size = size

class L1ICache(L1Cache):
    def __init__(self, size='16kB'):
        super().__init__(size=size)
        self.is_read_only = True

class L1DCache(L1Cache):
    def __init__(self, size='32kB'):
        super().__init__(size=size)

class L2Cache(Cache):
    assoc = 4
    size = '128kB'
    tag_latency = 15
    data_latency = 15
    response_latency = 15
    mshrs = 16
    tgts_per_mshr = 8

#========================================#

system = System()

system.clk_domain = SrcClockDomain()
system.clk_domain.clock = '1GHz'
system.clk_domain.voltage_domain = VoltageDomain()

system.mem_mode = 'timing'
system.mem_ranges = [AddrRange('512MB')]

system.cpu = X86TimingSimpleCPU()

# Configure caches hierarchy
system.cpu.icache = L1ICache(size='32kB')
system.cpu.dcache = L1DCache(size='64kB')
system.l2cache = L2Cache(size='256kB', assoc=8)
system.membus = SystemXBar()
system.l2bus = L2XBar()

# Connect CPU to L1 caches
system.cpu.icache_port = system.cpu.icache.cpu_side
system.cpu.dcache_port = system.cpu.dcache.cpu_side

# Connect L1 caches to L2 bus
system.cpu.icache.mem_side = system.l2bus.cpu_side_ports
system.cpu.dcache.mem_side = system.l2bus.cpu_side_ports

# Connect L2 caches to L2 bus and memory bus
system.l2cache.cpu_side = system.l2bus.mem_side_ports
system.l2cache.mem_side = system.membus.cpu_side_ports

system.cpu.createInterruptController()
system.cpu.interrupts[0].pio = system.membus.mem_side_ports
system.cpu.interrupts[0].int_requestor = system.membus.cpu_side_ports
system.cpu.interrupts[0].int_responder = system.membus.mem_side_ports

system.system_port = system.membus.cpu_side_ports

system.mem_ctrl = MemCtrl()
system.mem_ctrl.dram = DDR3_1600_8x8()
system.mem_ctrl.dram.range = system.mem_ranges[0]
system.mem_ctrl.port = system.membus.mem_side_ports

binary = "gem5/tests/test-progs/hello/bin/x86/linux/hello"
system.workload = SEWorkload.init_compatible(binary)

process = Process()
process.cmd = [binary]

system.cpu.workload = process
system.cpu.createThreads()

root = Root(full_system=False, system=system)
m5.instantiate()
print("Beginning simulation!")

exit_event = m5.simulate()
print("Exiting @ tick %i because %s" % (m5.curTick(), exit_event.getCause()))
