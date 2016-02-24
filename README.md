# kizzy
* kizzy is a X11 application-launcher for Linux, capable of launching .desktop files
* kizzy is tiny and aims to be less than 64kb. As of 2015-12-13 the release-build (with lots of space-reducing flags and using <a href="https://en.wikipedia.org/wiki/UPX">UPX</a>) is only 16kb on my system
* kizzy utilizes some C++14 features for easy to read code
* kizzy has few dependencies: X11
* kizzy is in-progress, and may very well die out any time. I'm a student with a busy schedule during semesters

## Building
`mkdir release && cd release && cmake -DCMAKE_BUILD_TYPE=Release .. && make` <br> `mkdir debug && cd debug && cmake -DCMAKE_BUILD_TYPE=Debug .. && make`

The release build uses lots of compiler-flags for reducing executable-size. Don't bother debugging it, for any debugging purpose whatsoever you should use the debug-build.

## Usage
kizzy will look for a configuration file ~/.config/kizzy/kizzy.conf that has the paths to directories in which kizzy will look for the .desktop files.
You _must_ create that file by yourself. My kizzy.conf looks like this:

<b>~/.config/kizzy/kizzy.conf</b>
```
~/.local/share/applications/
/usr/share/applications/
~/Desktop/
```

##Debugging
kizzy doesn't use any logging-system (a voice echoes in the wind "tiiiinyyyy...."). kizzy doesn't use standard output streams. For checking what went wrong, you could do: `./kizzy` followed by `echo $?` which will output a number. Those numbers are enum-values from <a href="https://github.com/Kuxe/kizzy/blob/master/include/statusdefs.hpp">statusdefs.hpp</a>. So, for example, if echo outputs 1 then are missing the kizzy.conf. Creating that file should fix error 1. 

## FAQ
<b>Q)</b><i> Why another application-launcher?</i><br>
<b>A)</b> Because most application-launchers that I've tried have been either pulling in unwanted dependencies or having high runtime memory-usage<p>

<b>Q)</b><i> dmenu already exists. What makes this different from dmenu?</i><br>
<b>A)</b> I intend to make the X11-UI for kizzy as appealing as X11-UI can be. Which is not very much. I think alfred and mutate looks awesome, I will try to accomplish a GUI similar to that of those only using X11 and still being nice on memory-usage. This might not be possible. We'll see how things turn out..<p>

<b>Q)</b><i> What features are planned?</i><br>
<b>A)</b> Not many. kizzy should remain tiny. Features don't go along with tinyness. Ergo.....<p>

<b>Q)</b><i> Dude your FAQ is way to tiny, I have this question/request/issue/crave for X, please fix X</i><br>
<b>A)</b> File an issue about it<p>
