# kizzy
* kizzy is a X11 application-launcher for Linux, capable of launching .desktop files
* kizzy is tiny, aims to be less than 64kb, as of 2015-08-04 the release-build (with lots of space-reducing flags) is only 24kb on my system
* kizzy utilizes some C++14 features for easy to read code
* kizzy has few dependencies:
** X11
** cmake
** make
** C++14-compliant compiler (only tested building on g++ 5.2.0)
* kizzy is in-progress, and may very well die out any time. I'm a student with a busy schedule during semesters

## Building
`mkdir release && cmake -DCMAKE_BUILD_TYPE=Release .. && make`
`mkdir debug && cmake -DCMAKE_BUILD_TYPE=Debug .. && make`

The release build uses lots of compiler-flags for reducing executable-size. Don't bother debugging it, for any debugging purpose whatsoever you should use the debug-build.

## Usage
kizzy will look for a configuration file ~/.config/kizzy/kizzy.conf that has the paths to directories in which kizzy will look for the .desktop files
You _must_ create that file by yourself. My kizzy.conf looks like this:

<b>~/.config/kizzy/kizzy.conf</b>
~/.local/share/applications/
/usr/share/applications/
~/Desktop/

## FAQ
<b>Q)</b> Why another application-launcher?
<b>A)</b> Because most application-launchers that I've tried have been either pulling in unwanted dependencies or having high runtime memory-usage

<b>Q)</b> dmenu already exists. What makes this different from dmenu?
<b>A)</b> I intend to make the X11-UI for kizzy as appealing as X11-UI can be. Which is not much. But still more than dmenu. I think alfred and mutate looks awesome, I will try to accomplish a GUI similar to that of those only using X11 and still being nice on memory-usage. This might not be possible. We'll see how things turn out..

<b>Q)</b> What features are planned?
<b>A)</b> Not many. kizzy should remain tiny. Features don't go along with tinyness. Ergo.....

<b>Q)</b> Dude your FAQ is way to tiny, I have this question/request/issue/crave for X, please fix X
<b>A)</b> File an issue about it
