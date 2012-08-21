BreakUp Plugin
=======

A jQuery plugin that fires custom events when configured breakpoints have been breached.


Summary
=======

Register callbacks with custom breakpoint events to support responsive development in browser. This plugin makes it easier to trigger javascript responsive step behaviors without writing custom breakpoint checking code.


API
=======

$.Breakup(breakpoints [, options,] selector [, arguments]) returns a BreakUp object.

**breakpoints** is an object whose properties are breakpoint minimum values, and whose values are functions. These functions will be called when a breakpoint is crossed. The 'this' context of the callback will be the set of selected elements. The first argument of the callback will be the *breakChanged* event. Additional arguments passed to the BreakUp function (see below) will be provided to the callback function.

```javascript
{
  'default': small,
  '450': narrow,
  '600': tablet,
  '750': desktop,
  '900': large
}
```

**options** (optional) is an object with the following possible values

<table>
  <thead>
    <tr>
      <th>Property</th>
      <th>Value</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>namespace</td>
      <td>A string representing a namespace for the breakChanged event.</td>
    </tr>
  </tbody>
</table>

**selector** is either a jQuery object of elements, a string selector that can be passed to the jQuery function or the window or document objects. BreakUp will not work without elements to act on. 

**arguments** is any number of argument of any type. They will all be passed to the breakpoint's callback function.

Examples
=======

See http://jessebeach.github.com/breakup/ for a live example.