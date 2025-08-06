Wiring Squad's modules for VCV Rack. Originally only Octoplus, but growing to encompass utilities and offshoots from it.

Octoplus is a distortion module for VCV Rack. It is a unique rectifier design whose activity can be triggered not only by the input signal itself, but by the first and second derivatives of the input signal(s), among other things. In addition to modifying the gain of the input signal, it can modify the first and second derivatives of that signal as well. Before and after the rectifier are two identical wavefolders, one before to affect the derivative sensing at the rectifier, and one after to keep the resulting signal below Rack's hardclip threshold. 

Octoplus is in a fairly early stage of development right now. Development is progressing rapidly on a day-by-day basis, but currently, only the pre-folder works, and in a limited capacity. The codebase is unrefined - major refactoring is coming.

PolySignalUtility is a standalone polyphonic CV generation utility for VCV Rack. It will be able to generate, manipulate, and mux between different banks of polyphonic CV. It could be used for many different things, but it's being designed especially to control Octoplus's per-voice filter settings.

PolySignalUtility is still a stub. It will come soon.

wsmodules is open to the public in pre-alpha under the MIT license. It will remain free and open-source forever. Feel free to use code from it in your own modules, especially the polyphonic code. But, I hereby release myself from any claims that the code is good or performant.

For questions, email me at wiringsquad@gmail.com.
