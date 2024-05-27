import serial
import numpy as np
from pyqtgraph.Qt import QtGui, QtCore, QtWidgets
import pyqtgraph as pg
import pyfilterbank as pf

import argparse

parser = argparse.ArgumentParser(
                    prog='2D_serial_plotter',
                    description='Read serial port and plot result',
                    epilog='Thanks 4 using me!')
parser.add_argument('--port', default = '/dev/ttyACM0', type = str, help="Serial port to read (default='/dev/ttyACM0')")
parser.add_argument('--baud', default = 115200, type = int, help="Baud rate of serial port (default=115200)")
parser.add_argument('--msfb', default = 20, type = int, help="Number of MSFB (default=20)")
parser.add_argument('--sample_window_size', default = 9, type = int, help="log_2 of fft size (default=9)")
parser.add_argument('--fs', default = 300e3, type = float, help="Sampling frequency (default=300e3)")
parser.add_argument('--lim', default = 200, type = int, help="Limit on the number of vectors shown (default=200)")

args = parser.parse_args()

from IPython.display import clear_output
limit = args.lim
melvecs = np.empty((0, args.msfb))

app = QtWidgets.QApplication([])
pli = pg.PlotItem()
imv = pg.ImageView(view=pli)
imv.show()

F_BOARD = args.fs
band = [10e3, 120e3]
buf_size = 2**args.sample_window_size
mmat, tup = pf.melbank.compute_melmat(num_mel_bands=args.msfb, freq_min=band[0], freq_max=band[1], num_fft_bands=buf_size//2+1, sample_rate=F_BOARD)
mmat = mmat.astype(np.float32)

boardmat = (mmat*2**15).astype(np.int16)
bin_to_freq = []
for i in range(len(mmat)):
    for k in range(1, len(mmat[i])-1):
        if mmat[i][k-1]< mmat[i][k] and mmat[i][k+1] < mmat[i][k]:
            bin_to_freq.append(np.fft.rfftfreq(buf_size, 1/F_BOARD)[k])

b_to_freq_tup = [(i, str(int(bin_to_freq[i]/1e3))) for i in range(len(bin_to_freq))]
pli.getAxis("left").setTicks([b_to_freq_tup])
pli.setAspectLocked(False)
with serial.Serial(args.port, args.baud, timeout=1) as ser:
    ser.reset_input_buffer()
    while True:
        
        line = ser.readline().decode('utf-8')   # read a '\n' terminated line
        ar = line.split(",")[:-1]

        try:
            ar = np.array([int(x) for x in ar], dtype=int)
        except: 
            pass
        
        if len(ar) == args.msfb:
            melvecs = np.concatenate([melvecs, ar[None, ...]], axis = 0)[-limit:]
            imv.setImage(melvecs)
            app.processEvents()
            
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(0)

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()