!function(e,t){"object"==typeof exports&&"object"==typeof module?module.exports=t():"function"==typeof define&&define.amd?define("AsuWebcore",[],t):"object"==typeof exports?exports.AsuWebcore=t():e.AsuWebcore=t()}(window,(function(){return function(e){function t(t){for(var r,a,s=t[0],c=t[1],l=t[2],p=0,b=[];p<s.length;p++)a=s[p],Object.prototype.hasOwnProperty.call(o,a)&&o[a]&&b.push(o[a][0]),o[a]=0;for(r in c)Object.prototype.hasOwnProperty.call(c,r)&&(e[r]=c[r]);for(d&&d(t);b.length;)b.shift()();return i.push.apply(i,l||[]),n()}function n(){for(var e,t=0;t<i.length;t++){for(var n=i[t],r=!0,s=1;s<n.length;s++){var c=n[s];0!==o[c]&&(r=!1)}r&&(i.splice(t--,1),e=a(a.s=n[0]))}return e}var r={},o={0:0},i=[];function a(t){if(r[t])return r[t].exports;var n=r[t]={i:t,l:!1,exports:{}};return e[t].call(n.exports,n,n.exports,a),n.l=!0,n.exports}a.m=e,a.c=r,a.d=function(e,t,n){a.o(e,t)||Object.defineProperty(e,t,{enumerable:!0,get:n})},a.r=function(e){"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},a.t=function(e,t){if(1&t&&(e=a(e)),8&t)return e;if(4&t&&"object"==typeof e&&e&&e.__esModule)return e;var n=Object.create(null);if(a.r(n),Object.defineProperty(n,"default",{enumerable:!0,value:e}),2&t&&"string"!=typeof e)for(var r in e)a.d(n,r,function(t){return e[t]}.bind(null,r));return n},a.n=function(e){var t=e&&e.__esModule?function(){return e.default}:function(){return e};return a.d(t,"a",t),t},a.o=function(e,t){return Object.prototype.hasOwnProperty.call(e,t)},a.p="";var s=window.webpackJsonpAsuWeb_name_=window.webpackJsonpAsuWeb_name_||[],c=s.push.bind(s);s.push=t,s=s.slice();for(var l=0;l<s.length;l++)t(s[l]);var d=c;return i.push([13,1]),n()}({13:function(e,t,n){"use strict";n.r(t),n.d(t,"Button",(function(){return O})),n.d(t,"FoldableCard",(function(){return _})),n.d(t,"Header",(function(){return et})),n.d(t,"Heading",(function(){return Pe})),n.d(t,"Icon",(function(){return H})),n.d(t,"Nav",(function(){return Me})),n.d(t,"Panel",(function(){return nt})),n.d(t,"Login",(function(){return Xe})),n.d(t,"Title",(function(){return Qe})),n.d(t,"Navbar",(function(){return Ke})),n.d(t,"Search",(function(){return qe})),n.d(t,"UniversalSearch",(function(){return We})),n.d(t,"Logo",(function(){return Je})),n.d(t,"HydratePreact",(function(){return o})),n.d(t,"RenderPreact",(function(){return i})),n.d(t,"initHeader",(function(){return s})),n.d(t,"checkSSOCookie",(function(){return a}));var r=n(0);const o=(e,t,n)=>Object(r.i)(Object(r.h)(e,t),n),i=(e,t,n)=>Object(r.k)(Object(r.h)(e,t),n),a=()=>{let e={userName:"",loggedIn:!1};const t=document.cookie.split(";");for(let n=0;n<t.length;n++)if(t[n].indexOf("SSONAME")>0){if(""==t[n].substring(9))break;e.userName=t[n].substring(9),e.loggedIn=!0;break}return e},s=(e,t=!1,n="headerContainer")=>{const{loggedIn:r,userName:s,loginLink:c,...l}=e,d=c||(e=>{let t;const n=window.location.toString();return t=decodeURI(e),t=t.replace("/login","/login?callapp="+n),t})(Xe.defaultProps.loginLink),p={...r&&s?{loggedIn:r,userName:s}:a(),...l,loginLink:d};t?o(et,p,document.getElementById(n)):i(et,p,document.getElementById(n))};var c=n(3),l=n(2),d=n(1),p=n.n(d);const b=l.a`
  position: absolute;
  width: 1px;
  height: 1px;
  margin: -1px;
  padding: 0;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
`,h=l.a`
  :not(:focus):not(:active) {
    clip: rect(0 0 0 0);
    clip-path: inset(100%);
    height: 1px;
    overflow: hidden;
    position: absolute;
    white-space: nowrap;
    width: 1px;
  }
`;function u(){return(u=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const f=Object(c.c)(({disabled:e,small:t,medium:n,large:o,gold:i,maroon:a,dark:s,type:c,...d},p)=>{const b="link"==c?"a":"button",h=d.light?d.light:()=>!(i||s||a);return Object(r.h)(b,u({},d,{class:Object(l.b)(l.a`
            text-decoration: none;
            font-weight: bold;
            display: inline-block;
            color: #191919;
            text-align: center;
            text-decoration: none;
            vertical-align: middle;
            user-select: none;
            background-color: transparent;
            border: 1px solid transparent;
            padding: 1rem 2rem;
            font-size: 1rem;
            line-height: 1rem;
            border-radius: 400rem;
            transition: 0.03s ease-in-out;

            :not(:disabled):not(.disabled) {
              cursor: pointer;
            }

            :hover {
              transform: ${"scale(1.1)"};
            }

            :active {
              transform: ${"scale(1)"};
            }

            ${e&&l.a`
              opacity: ${"50%"};
            `}

            ${t&&l.a`
              font-size: ${"0.75rem"};
              height: ${"1.375rem"};
              min-width: ${"4rem"};
              padding: ${"0.25rem"}
                ${".75rem"};
            `}

        ${n&&l.a`
              font-size: 0.875rem;
              padding: 0.5rem 1rem;
            `}

        ${o&&l.a`
              font-size: ${"2rem"};
              height: ${"3rem"};
              min-width: ${"8rem"};
            `}

        ${i&&l.a`
              color: ${"#191919"};
              background-color: ${"#ffc627"};

              :hover {
                color: ${"#191919"};
              }
            `}

        ${a&&l.a`
              color: #ffffff;
              background-color: #8c1d40;
              border-color: #8c1d40;

              :visited:not(.btn) {
                color: #ffffff;
              }
            `}

        ${s&&l.a`
              color: ${"#fafafa"};
              background-color: ${"#191919"};

              :visited:not(.btn) {
                color: ${"#fafafa"};
              }
            `}

        ${h&&l.a`
              color: ${"#191919"};
              background-color: ${"#bfbfbf"};
            `}
          `,d.class),ref:p}),d.children)});f.propTypes={type:p.a.string,href:p.a.string,dark:p.a.bool,light:p.a.bool,gold:p.a.bool,maroon:p.a.bool,disabled:p.a.bool,small:p.a.bool,medium:p.a.bool,large:p.a.bool,onFocus:p.a.func},f.defaultProps={disabled:!1};const m=l.a`
  .btn {
    text-decoration: none;
    font-weight: bold;
    display: inline-block;
    color: #191919;
    text-align: center;
    text-decoration: none;
    vertical-align: middle;
    user-select: none;
    background-color: transparent;
    border: 1px solid transparent;
    padding: 1rem 2rem;
    font-size: 1rem;
    line-height: 1rem;
    border-radius: 400rem;
    transition: 0.03s ease-in-out;

    :not(:disabled):not(.disabled) {
      cursor: pointer;
    }

    :hover {
      transform: ${"scale(1.1)"};
    }

    :active {
      transform: ${"scale(1)"};
    }

    &.btn-disabled {
      opacity: ${"50%"};
    }

    &.btn-small {
      font-size: ${"0.75rem"};
      height: ${"1.375rem"};
      min-width: ${"4rem"};
      padding: ${"0.25rem"} ${".75rem"};
    }

    &.btn-medium {
      font-size: ${"0.875rem"};
      height: ${"2rem"};
      min-width: ${"5rem"};
      padding: ${"0.5rem"} ${"1rem"};
    }

    &.btn-large {
      font-size: ${"2rem"};
      height: ${"3rem"};
      min-width: ${"8rem"};
    }

    &.btn-gold {
      color: ${"#191919"};
      background-color: ${"#ffc627"};
    }

    &.btn-maroon {
      color: ${"#fafafa"};
      background-color: ${"#8c1d40"};
    }

    &.btn-dark {
      color: ${"#fafafa"};
      background-color: ${"#191919"};
    }

    &.btn-light {
      color: ${"#191919"};
      background-color: ${"#bfbfbf"};
    }
  }
`;function g(){return(g=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const O=Object(c.c)(({href:e,children:t,...n},o)=>{const i=e?"link":"button";return Object(r.h)(f,g({type:i,ref:o},e?{href:e}:{},n),t)});O.propTypes={type:p.a.string,href:p.a.string,gold:p.a.bool,maroon:p.a.bool,disabled:p.a.bool,small:p.a.bool,medium:p.a.bool,large:p.a.bool,itemRef:p.a.oneOfType([p.a.func,p.a.shape({current:p.a.instanceOf(p.a.element)})]),onFocus:p.a.func},O.defaultProps={disabled:!1};var y=n(4),v=n(5);function j(){return(j=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const w=e=>Object(r.h)(y.a,j({icon:v.a},e)),x=e=>Object(r.h)(y.a,j({icon:v.l},e)),k=e=>Object(r.h)(y.a,j({icon:v.c},e)),$=e=>Object(r.h)(y.a,j({icon:v.k},e)),z=e=>Object(r.h)(y.a,j({icon:v.f},e)),P=e=>Object(r.h)(y.a,j({icon:v.e},e)),T=e=>Object(r.h)(y.a,j({icon:v.j},e)),S=e=>Object(r.h)(y.a,j({icon:v.g},e)),L=e=>Object(r.h)(y.a,j({icon:v.b},e)),F=e=>Object(r.h)(y.a,j({icon:v.i},e)),I=e=>Object(r.h)("span",{class:Object(l.b)("fa-layers fa-fw",e.class)},Object(r.h)(y.a,{icon:v.d,size:"2x"}),Object(r.h)(y.a,{icon:v.m,size:"1x"})),U=e=>Object(r.h)(y.a,j({icon:v.h},e)),H=({type:e,...t})=>{switch(e){case"mobile":return Object(r.h)($,null);case"chevron-down":return Object(r.h)(k,t);case"search":return Object(r.h)(x,t);case"desktop":return Object(r.h)(z,t);case"clipboard":return Object(r.h)(P,t);case"map-pin":return Object(r.h)(T,t);case"exclamation-triangle":return Object(r.h)(S,t);case"bell":return Object(r.h)(L,t);case"info-circle":return Object(r.h)(F,t);case"circle-close":return Object(r.h)(I,t);case"bars":return Object(r.h)(w,t);case"home":return Object(r.h)(U,t);default:return""}};function M(){return(M=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}H.propTypes={type:p.a.string.isRequired},H.defaultProps={};const C=({show:e,id:t,...n})=>Object(r.h)("div",M({},t?{id:t}:{},{class:Object(l.b)(l.a`
          padding: 0 32px 24px 32px;
          flex-grow: 100;
          flex: 1 1 auto;
          min-height: 1px;
          padding: 1.25rem;
          ${!e&&l.a`
            display: none;
          `}
        `,n.class),dangerouslySetInnerHTML:{__html:n.children}})),D=e=>Object(r.h)("div",{class:Object(l.b)(l.a`
          position: relative;
          display: -webkit-box;
          display: -ms-flexbox;
          display: flex;
          flex-direction: column;
          min-width: 0;
          word-wrap: break-word;
          background-color: #ffffff;
          background-clip: border-box;
          border: 1px solid rgba(0, 0, 0, 0.125);
          border-radius: 0;
          border-color: #d0d0d0;
          border-left: 0.5rem solid #ffc627;
          height: auto;
        `,e.class)},e.children),N=({show:e,id:t,...n})=>Object(r.h)(C,M({},t?{id:t}:{},{show:e,class:Object(l.b)(l.a`
          ${e&&l.a`
            border-top: 1px solid #d0d0d0;
          `}
        `,n.class)}),n.children),R=({show:e,id:t,...n})=>Object(r.h)("button",M({"aria-expanded":e},t?{"aria-controls":t}:{},{role:"button",class:l.a`
        padding: 32px 32px 16px 32px;
        flex-grow: 1;
        padding-bottom: 0;
        padding: 0.75rem 1.25rem;
        margin-bottom: 0;
        background-color: rgba(255, 255, 255, 0.03);
        display: flex;
        flex-direction: row;
        align-items: baseline;
        justify-content: space-between;
        cursor: pointer;
        border: 0;

        h4 {
          display: flex;
          flex-direction: row;
          align-items: baseline;

          a {
            padding: 0.5rem 1.5rem;
            color: #191919;
            text-decoration: none;
            display: flex;
            flex-direction: row
            flex-wrap: nowrap;
            justify-content: space-between;
            align-items: center;
          }
        }

        .fa-chevron-down {
          transition-duration: 0.4s;
          font-size: 1.25rem;
        }

        ${e?l.a`
                .fa-chevron-down {
                  transform: rotate(-180deg);
                }
              `:""}

      `},n),n.children,Object(r.h)(H,{type:"chevron-down"})),_=({head:e,children:t,id:n,...o})=>{const[i,a]=Object(c.g)(!1);return Object(r.h)(D,{class:o.class},Object(r.h)(R,{show:i,id:n,onClick:e=>{a(e=>!e)}},e),Object(r.h)(N,{show:i,id:n},t))};function A(){return(A=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}_.propTypes={head:p.a.node,children:p.a.node,class:p.a.string,id:p.a.string},_.defaultProps={};const E=e=>l.a`
  .navlist {
    list-style: none;
    display: flex;
    margin: 0;
    padding: 0;
    align-items: flex-end;

    a {
      text-decoration: none;
    }

    > li {
      position: relative;
      padding: 0;
      border: 0;
      margin-right: 0.5rem;

      &.active,
      &.dropdown-open, :hover {
        > a:after {
          width: 100%;
        }
      }

      > a {
        :after {
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
          content: "";
          display: block;
          height: 0.5rem;
          background-color: #ffc627;
          position: relative;
          bottom: 0;
          width: 0;
          margin-left: 0;
          top: .5rem;
        }
      }

      @media (min-width: ${e}) {
        position: static;

        &.dropdown-open,
        &.active {
          > a:after {
            width: calc(100% + 24px);
            margin-left: 0;
          }
        }

        > a {

          line-height: 1rem;


          box-sizing: content-box;
          :hover {
            :after {
              width: calc(100% + 24px);
              margin-left: 0;
            }
          }

          :after {
            transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
            content: '';
            display: block;
            height: .5rem;
            background-color: #ffc627;
            position: relative;
            top: .5rem;
            bottom: 0;
            width: 0;
            left: -.75rem;
            margin-left: 0;
          }
        }
      }

      @media (max-width: ${e}) {

        > a:after {
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
          content: "";
          display: block;
          height: 0.5rem;
          background-color: #ffc627;
        }
      }

      > a {
        display: block;
        padding: 0.5rem 0.75rem;
        color: #191919;

        svg.fa-chevron-down {
          transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

          &.open {
            transform: rotate(180deg);
          }
        }
      }
    }

    .mobile-only {
      ${b}
    }

    @media (min-width: ${e}) {
      svg.fa-chevron-down {
        float: none;
        display: inline-block;
        font-size: 0.75rem;
        margin-left: 0.5rem;
      }
    }

    @media (max-width: ${e}) {
      flex-direction: column;
      align-items: stretch;
      padding: 0;

      > li {
        margin-right: 0;

        > a {
          padding: 1rem 1rem .5rem 1rem;
          justify-content: space-between;
          display: block;
          border-bottom: 1px solid #cccccc;
          align-items: center;

          > svg {
            float: right;
            font-size: 1.25rem;
          }
        }

        :first-of-type {
          border-top: 1px solid #cccccc;
        }

        :last-of-type {
          border-bottom: none;
        }
      }

      .mobile-only {
        ${(e=>{const t=e||"relative";return l.a`
    width: auto;
    height: auto;
    margin: 0;
    overflow: visible;
    border: none;
    clip: auto;
    position: ${t};
  `})()}
      }
    }
  }
`,q=Object(c.c)(({children:e,...t},n)=>Object(r.h)("ul",A({ref:n,"aria-label":"ASU"},t,{class:Object(l.b)(t.class,"navlist")}),e)),W=e=>Object(r.h)("form",{class:"navbar-site-buttons"},e.children),X=e=>Object(r.h)("div",{class:Object(l.b)("dropdown",e.open?"open":"",e.class)},Object(r.h)("div",null,e.children),e.buttons?Object(r.h)("div",null,e.buttons):""),B=e=>Object(r.h)("ul",{class:Object(l.b)("menu-column",e.open?"open":"")},e.children),K=e=>l.a`
  ul {
    list-style: none;
    a {
      text-decoration: none;
    }
  }

  .mobile-only {
    ${b}
  }

  @media (min-width: ${e}) {
    width: 100%;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    padding: 0;
    margin: 0;

    svg.fa-chevron-down {
      float: none;
      display: inline-block;
      font-size: 0.75rem;
      margin-left: 0.5rem;
    }
  }

  @media (max-width: ${e}) {
    border: none;
    display: none;
    flex-direction: column;
    width: 100%;

    &.open-nav,
    &:target {
      overflow-y: scroll;
      display: flex;
    }
  }

  ${(e=>l.a`
  /** DdMenu CSS **/
  div.dropdown {
    position: absolute;
    display: flex;
    justify-content: space-between;
    background: #ffffff;
    border: 1px solid #d0d0d0;
    border-top: none;
    opacity: 0;
    visibility: hidden;
    z-index: 999;
    flex-wrap: nowrap;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    overflow: hidden;
    margin: -1px 0 0 0;
    flex-direction: column;

    > div {
      width: 100%;
    }

    &.mega {
      width: 100%;
      left: 0;
      border-right: none;
      border-left: none;

      > div {
        max-width: ${"1224px"};
      }
    }

    &.open {
      visibility: visible;
      opacity: 1;
    }

    h3 {
      font-size: 1.5rem;
      letter-spacing: -0.035em;
      font-weight: 700;
      text-align: left;
      opacity: 1;
      margin: 1rem 0;
      line-height: calc(100% + 0.12em);
    }

    @media (max-width: ${e}) {
      padding-left: 3rem;
      flex-direction: column;
      max-height: 0;
      border: none;

      &.open {
        position: relative;
        display: flex;
        max-height: 10000px;
      }
    }

    @media (min-width: ${e}) {
      position: fixed;

      &:not(.mega) .menu-column {
        min-width: 16rem;
      }

      > div {
        padding: 2rem;
        display: flex;
        margin: 0 auto;
        justify-content: center;
      }

      &.open {
        border-bottom: 1px solid #d0d0d0;
      }

      h3 {
        margin-top: 0;
      }
    }
  }
`)(e)}
  ${(e=>l.a`
  /** Dropdown Menu Column CSS **/
  ul.menu-column {
    display: flex;
    flex-direction: column;
    border-right: 1px solid #d0d0d0;
    padding: 0 2rem;
    position: relative;

    :last-child {
      border-right: none;
    }

    @media (min-width: ${e}) {
      width: 16rem;
      padding: 0 1.5rem 0 0;
      border-right: 1px solid #bfbfbf;
      margin-right: 1.5rem;
      max-width: 282px;

      :last-of-type {
        margin-right: 0;
        padding-right: 0;
        border-right: 0;
      }
    }

    @media (max-width: ${e}) {
      border-right: none;
      width: 100%;
      padding: 0;
      > li {
        :last-of-type {
          border: none;
        }
      }
    }

    @media (min-width: ${e}) {
      padding: 0 1.5rem 0 0;
      border-right: 1px solid #bfbfbf;
      margin-right: 1.5rem;

      flex: 1;
      max-width: 282px;

      > li {
        padding: 0;
        margin: 0;
      }
    }
  }
`)(e)}
  ${(e=>l.a`
  form.navbar-site-buttons {
    display: flex;
    align-items: flex-end;
    padding-bottom: 3px;

    a + a {
      margin-left: 1rem;
    }

    @media (max-width: ${e}) {
      padding: 1rem 2rem;
    }
  }
`)(e)}
  ${E(e)}
`,G=e=>l.a`
  nav.header-nav {
    ${K(e)}
  }
`,J=({open:e,maxMobileHeight:t,injectStyles:n,breakpoint:o,handleKeyDown:i,children:a,...s})=>{const c=-1==t?"75vh":t+"px",d="Xl"===o?"1260px":"992px";return Object(r.h)("nav",A({id:"asu-header-nav",class:Object(l.b)("header-nav",e?"open-nav":"",l.a`
          @media (max-width: ${d}) {
            &.open-nav,
            &:target {
              flex-direction: column;
              width: 100%;

              max-height: ${c};
              display: flex;
            }
          }
        `,n?K(d):"")},s),a)};function Y(){return(Y=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Q=e=>l.a`
  .asu-search-form {
    > form {
      display: flex;
      flex-flow: row wrap;
      align-items: center;

      label {
        position: relative;
        margin-left: -95px;
        font-weight: 400;
        transition: all 0.5s;
        color: #747474;
        display: none;
      }

      > input {
        background: url('data:image/svg+xml;utf8,<svg aria-hidden="true" focusable="false" data-prefix="fas" data-icon="search" class="svg-inline--fa fa-search fa-w-16 " role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 512 512"><path fill="currentColor" d="M505 442.7L405.3 343c-4.5-4.5-10.6-7-17-7H372c27.6-35.3 44-79.7 44-128C416 93.1 322.9 0 208 0S0 93.1 0 208s93.1 208 208 208c48.3 0 92.7-16.4 128-44v16.3c0 6.4 2.5 12.5 7 17l99.7 99.7c9.4 9.4 24.6 9.4 33.9 0l28.3-28.3c9.4-9.4 9.4-24.6.1-34zM208 336c-70.7 0-128-57.2-128-128 0-70.7 57.2-128 128-128 70.7 0 128 57.2 128 128 0 70.7-57.2 128-128 128z"></path></svg>') no-repeat 10px 50%;
        background-size: 12px;

      }
    }

    > a {
      display: inline-block;
      font-size: 0.75rem;
      color: #484848;
    }

    @media (max-width: ${e}) {
      width: 100%;
      display: flex;
      order: -1;

      > form {
        width: 100%;
        display: flex;
        align-items: center;
        padding: 1rem 2rem;

        > input {
          padding: 0.5rem 2rem;
          display: flex;
          width: 100%;
          border: 0;
          background-color: #FFFFFF;
        }

        > button {
          font-size: 1rem;
          opacity: 0.75;
        }
      }

      > a {
        display: none;
      }

      button {
        width: 2.5rem;
        height: 2.5rem;
      }


    }

    button {
      font-size: 0.75rem;
      border: none;
      background: transparent;
      cursor: pointer;
      margin-right: -30px;
      z-index: 20;
      width: 1.5rem;
      height: 1.5rem;
      padding: 0;
    }

    @media (min-width: ${e}) {
      > form {
        justify-content: flex-end;
      }

      input {
        background-size: 16px;
        width: 32px;
        cursor: pointer;
        font-size: 0.75rem;
        line-height: 0.75rem;
        border: 0;
        border-radius: 0;
        padding: 0.25rem;
        transition: all 0.5s;
      }

      .show-search-input {
        > input {
          display: inline-flex;
          width: 200px;
          color: #747474;
          background-color: #fff;
          cursor: auto;
          margin: 0.5rem 0;
          padding-left: 32px;
          visibility: visible;
          height: calc(1.5em + 0.75rem + 2px);

          :valid + label {
            display: none;
          }
        }

        label {
          display: block;
          margin-bottom: 0;
          font-size: inherit;
        }
      }
    }
  }
`,V=e=>Object(r.h)("div",Y({class:Object(l.b)("asu-search-form",e.class)},e),e.children),Z=e=>l.a`
  .login-status {
    font-size: 0.75rem;
    display: flex;
    align-items: center;
    margin-right: 0.5rem;
    padding: 0.25rem 0.5rem 0.25rem 0.5rem;


    > a, span {
      padding: 0;
      margin: 0;
      color: #484848;
      text-decoration: none;
    }
    .name {
      font-weight: 700;
    }

    .signout:before {
      content: "(";
      margin-left: 4px;
    }

    .signout:after {
      content: ") ";
    }


    @media (min-width: ${e}) {
      margin-left: .5rem;
    }
  }
`,ee=e=>Object(r.h)("div",{class:Object(l.b)(e.class,"login-status")},e.children);function te(){return(te=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const ne=e=>l.a`
  .navbar-brand {
    display: inline-block;
    padding-top: 0.3125rem;
    padding-bottom: 0.3125rem;
    margin-right: 1rem;
    font-size: 1.25rem;
    line-height: inherit;
    white-space: nowrap;
    padding: 0;
    margin: 0;

    .horiz {
      display: none;
      transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    }

    .vert {
      @media (min-width: 992px) {
        display: block;
        height: 72px;
        width: auto;
        margin: 1.5rem 1rem 1.5rem 0;
      }
    }

    img {
      height: 80px;
    }

    @media (max-width: ${e}) {
      img {
        float: none;
        height: 32px;
      }

      .vert {
        display: none;
      }
      .horiz {
        display: block;
        height: 32px;
        width: auto;
        margin-bottom: 1rem;
        margin-left: 2rem;
      }
    }
  }

  &.scrolled .navbar-component .navbar-brand d img {
    height: 64px;
  }

  @media (max-width: ${e}) {
    &.scrolled .navbar-component .navbar-brand d img {
      height: 28px;
    }

    &.scrolled .navbar-brand .horiz {
      margin-bottom: 0.5rem;
    }
  }
`,re=Object(c.c)(({brandLink:e,src:t,mobileSrc:n,alt:o,...i},a)=>Object(r.h)("a",te({href:e,class:"navbar-brand",ref:a},i),Object(r.h)("img",{class:"vert",src:t,alt:o}),Object(r.h)("img",{class:"horiz",src:n,alt:o}))),oe=e=>l.a`
  .title {
    line-height: 1;
    font-size: 1rem;
    font-weight: 700;
    margin: 0 2rem 1.5rem 2rem;
    letter-spacing: -1px;
    background-image: linear-gradient(to right,transparent 51%,#FFC626 51%,95%,transparent);
    background-position: 0 0;
    background-size: 200%;
    display: inline-block;
    /*padding-right: 4px;*/
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
    transition-duration: 1s;

    &.active {
      background-position: -200%;
    }

    > .unit-name {
      display: none;
    }

    .unit-name,
    .subunit-name,
    &.subunit-name {
      color: #191919;
    }

    @media (min-width: ${e}) {
      line-height: 1;
      font-weight: 700;
      padding: 0;
      margin: 1rem 0 0.5rem 0;

      > .unit-name {
        font-size: 1rem;
        margin-bottom: 0.5rem;
        display: block;
      }

      &.subunit-name {
        font-size: 2rem;
        margin: 1.5rem 0 1rem 0;
        font-weight: 700;
      }

      .subunit-name {
        font-size: 1.5rem;
        margin-bottom: 0;
      }
    }
  }

  &.scrolled .title {
    padding-bottom: 1rem;
  }

  @media (min-width: ${e}) {
    &.scrolled .title.subunit-name {
      font-size: 1.5rem;
    }

    &.scrolled .title {
      padding-bottom: 0;
    }
  }
`,ie=Object(c.c)(({children:e,parentOrg:t,baseUrl:n,parentOrgUrl:o,...i},a)=>t?Object(r.h)("div",{class:Object(l.b)("title",i.class),ref:a},Object(r.h)("a",{class:"unit-name",href:o},t),Object(r.h)("a",{class:"subunit-name",href:n},e)):Object(r.h)("a",{class:Object(l.b)("title","subunit-name",i.class),href:n,ref:a},e));function ae(){return(ae=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const se=e=>l.a`
  .navlink,
  .navicon {
    padding: 0.5rem 0;

    > a {
      padding: 8px;
      position: relative;
      color: #191919;

      &.nav-item {
        display: block;
      }
    }

    @media (max-width: ${e}) {
      border-bottom: 1px solid #cccccc;

      .icon-nav-item {
        ${b}
      }
    }
  }

  .navlink {
    @media (min-width: ${e}) {
      > a {
        padding: 0.5rem 0;
        white-space: normal;

        :visited {
          color: #191919;
        }

        :hover {
          color: #8c1d40;
          text-decoration: underline;
        }
      }
    }
  }

  .navbutton {
    margin-top: 1rem;

    @media (min-width: ${e}) {
      position: absolute;
      bottom: 0;
      margin: 0;
    }
  }
`,ce=Object(c.c)(({onFocus:e,text:t,...n},o)=>Object(r.h)("li",{class:"navlink"},Object(r.h)("a",ae({},n,{class:Object(l.b)("nav-item",n.class)},e?{onFocus:e}:"",{ref:o}),t))),le=Object(c.c)(({children:e,onFocus:t,type:n,...o},i)=>Object(r.h)("li",{class:"navicon"},Object(r.h)("a",ae({},o,{class:o.class?o.class:""},t?{onFocus:t}:"",{ref:i}),Object(r.h)(H,{type:n,className:"icon-nav-item"}),Object(r.h)("span",{class:"mobile-only"},e)))),de=Object(c.c)(({children:e,...t},n)=>Object(r.h)("li",{class:Object(l.b)("navbutton",t.class)},Object(r.h)(O,ae({},t,{ref:n,medium:!0,dark:!0}),e)));function pe(){return(pe=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const be=e=>l.a`
  .navbar-toggler {
    padding: 0.25rem 0.75rem;
    font-size: 1.25rem;
    line-height: 1;
    background-color: transparent;
    border-radius: 400rem;
    outline: 0;
    color: #191919;
    border: 0;
    margin-right: 2rem;
    cursor: pointer;
    align-self: flex-start;

    @media (min-width: ${e}) {
      display: none;
    }
  }
`,he=({mobileOpen:e,...t})=>Object(r.h)("button",pe({},t,{class:Object(l.b)(l.a`
          .fa-circle {
            color: #e8e8e8;
            font-size: 1rem;
            margin-left: -12px;
            height: 2em;
            width: 2.5em;
          }

          svg.svg-inline--fa.fa-times {
            height: 1em;
            width: 1.25em;
            margin-left: 7px;
          }
        `,"navbar-toggler")}),e?Object(r.h)(H,{type:"circle-close"}):Object(r.h)(H,{type:"bars",href:"#asu-header-nav"})),ue=e=>l.a`
  .navbar-component {
    background-color: #ffffff;
    display: flex;
    width: 100%;
    padding-right: 12px;
    padding-left: 12px;
    margin-right: auto;
    margin-left: auto;
    max-width: ${"1224px"};

    > div {
      display: flex;
      flex-direction: row;
      width: 100%;
      align-items: flex-start;
      transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
      position: relative;
      align-items: flex-end;
    }

    @media (max-width: ${e}) {
      order: -1;
      display: flex;
      top: 0;
      width: 100%;
      height: auto;
      background-color: #ffffff;
      padding: 0;
      z-index: 1600;
      padding: ${"24px"} 0 0 0;

      > div {
        padding: 0;
        flex-wrap: wrap;
        justify-content: space-between;
      }
    }
  }
`,fe=({children:e,...t})=>Object(r.h)("div",{class:"navbar-component"},Object(r.h)("div",null,e)),me=e=>l.a`
  .navbar-container {
    display: flex;
    width: 100%;
    flex-direction: column;
    align-items: flex-start;

    @media (max-width: ${e}) {
      width: 100%;
    }
  }
`,ge=e=>Object(r.h)("div",{class:Object(l.b)("navbar-container",e.class)},e.children);function Oe(){return(Oe=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const ye=({children:e,breakpoint:t,...n})=>Object(r.h)(r.b,null,Object(r.h)("div",{id:"asu-report-accessiblity"},Object(r.h)("a",{href:"https://www.asu.edu/accessibility/",class:l.a`
            ${h}
          `},"Report an accessibility problem")),Object(r.h)("header",Oe({},n,{class:Object(l.b)(n.class,l.a`
            *,
            *:before,
            *:after {
              box-sizing: border-box;
            }

            :focus {
              outline: 0;
              box-shadow: 0 0 8px #00baff !important;
            }

            a {
              cursor: pointer;
              text-decoration: none;
            }

            padding: 0;
            display: flex;
            flex-direction: column;
            position: fixed;
            width: 100%;
            z-index: 999;
            background: #ffffff;
            border-bottom: 1px solid #d0d0d0;
            transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
            top: 0;
            left: 0;

            div,
            h1 {
              font-family: Arial, sans-serif;
            }

            &.scrolled {
              transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);
            }

            @media (max-width: ${t}) {
              &.scrolled .navbar-component .header-title h1 {
                font-size: 1rem;
              }
            }
          `,ue(t),G(t),m,me(t),ne(t),ve(t),Q(t),oe(t),Z(t),be(t),se(t))}),e)),ve=e=>l.a`
  .universal-nav {
    padding: 0 2rem;
    display: flex;
    justify-content: center;
    background-color: #e8e8e8;
    height: 24px;
    transition: 0.5s cubic-bezier(0.19, 1, 0.19, 1);

    > div {
      width: 100%;
      max-width: ${"1224px"};
      display: flex;
      flex-wrap: wrap;
      align-items: center;
      justify-content: flex-end;

      > div {
        > a {
          display: inline-flex;
          font-size: 0.75rem;
          padding: 0.25rem 0.5rem;
          color: #484848;
          margin: 0;
        }
      }
    }

    @media (max-width: ${e}) {
      display: none;
      padding: 0;
      transition: none;
      height: auto;

      &.mobile-open {
        z-index: 998;
        width 100%;
        display: flex;
        justify-content: center;
      }

      .nav-grid {
        display: grid;
        grid-template-columns: 1fr 1fr;
        grid-auto-flow: row;
        justify-items: start;
        width: 100%;

        > a, div {
          color: #191919;
          margin-right: 0;
          text-align: center;
          width: 100%;
          font-size: 0.875rem;
          padding: 1rem 1.5rem;
          border-top: 1px solid #d0d0d0;
          display:block;

          :nth-child(even) {
            border-left: 1px solid #d0d0d0;
          }
        }
      }

    }
  }

  @media (min-width: ${e}) {
    &.scrolled .universal-nav {
      height: 0;
      overflow: hidden;
    }

    .universal-nav {
      &.search-open {
        height: 48px;
      }

      .nav-grid {
        display: flex;
      }
    }
  }
`,je=Object(c.c)((e,t)=>Object(r.h)("div",{class:Object(l.b)("universal-nav",e.open?"mobile-open":"",e.searchOpen?"search-open":""),ref:t},Object(r.h)("div",null,e.children))),we=({children:e,...t})=>Object(r.h)("div",{class:Object(l.b)("nav-grid",t.class)},e);function xe(){return(xe=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const ke=l.a`
  font-weight: 700;
  text-align: left;
  opacity: 1;
  margin: 1rem 0;
  line-height: calc(100% + 0.12em);
`,$e=({children:e,...t})=>Object(r.h)("h4",xe({},t,{class:Object(l.b)(l.a`
          ${ke}
          font-size: 1.25rem;
          letter-spacing: -0.025em;
        `,t.class)}),e),ze=({children:e,...t})=>Object(r.h)("h3",xe({},t,{class:Object(l.b)(l.a`
          ${ke}
          font-size: 1.5rem;
          letter-spacing: -0.035em;
        `,t.class)}),e),Pe=({type:e,...t})=>{switch(e){case"h4":return Object(r.h)($e,{class:t.class},t.children);case"h3":return Object(r.h)(ze,{class:t.class},t.children);default:return""}};function Te(){return(Te=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Pe.propTypes={type:p.a.string.isRequired},Pe.defaultProps={};const Se=Object(c.c)(({onFocus:e,type:t,children:n,href:o,...i},a)=>{switch(t){case"button":return Object(r.h)(de,Te({},i,{ref:a,href:o},e?{onFocus:e}:"",{medium:!0,dark:!0}),n);case"icon":return Object(r.h)(le,Te({},i,{href:o},e?{onFocus:e}:"",{ref:a,type:i.class}),n);case"heading":return Object(r.h)(Pe,{type:"h3"},n);default:return Object(r.h)(ce,Te({href:o},e?{onFocus:e}:"",{ref:a},i),n)}});Se.propTypes={location:p.a.array,onFocus:p.a.func,type:p.a.string,href:p.a.string,children:p.a.string.isRequired,icon:p.a.string},Se.defaultProps={};var Le=Se;function Fe(){return(Fe=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Ie=Object(c.c)(({text:e,setFocus:t,pIndex:n,isOpen:o,setOpen:i,children:a,mega:s,buttons:c,href:l,...d},p)=>{const b=e=>{i(o?-1:e)};return Object(r.h)("li",{class:o?"dropdown-open":""},Object(r.h)("a",Fe({},d,{role:"button","aria-expanded":o,onMouseDown:e=>{e.preventDefault(),b(n)},onKeyDown:e=>{const t=e.keyCode;32!=t&&13!=t||b(n)},onFocus:e=>{t([n,-1,-1])},tabIndex:"0",ref:p}),e," ",Object(r.h)(k,{sr:e,className:o?"open":""})),Object(r.h)(X,Fe({open:o},{class:s?"mega":""},c?{buttons:c.map((e,t)=>Object(r.h)(O,{href:e.href,color:e.color},e.text))}:{}),a))});Ie.propTypes={setFocus:p.a.func.isRequired,pIndex:p.a.number.isRequired,isOpen:p.a.bool,setOpen:p.a.func.isRequired,buttons:p.a.arrayOf(p.a.object),mega:p.a.bool,text:p.a.string},Ie.defaultProps={isOpen:!1};var Ue=Ie;function He(){return(He=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const Me=({navTree:e,width:t,height:n,mobileOpen:o,maxMobileHeight:i,buttons:a,injectStyles:s,breakpoint:l,...d})=>{const[p,b]=Object(c.g)([-1,-1,-1]),[h,u]=Object(c.g)(-1),f=e=>{b(e)},m=parseInt("Xl"===l?"1260px":"992px",10),g=Object(c.e)(()=>e.map(e=>{const t=Object(c.a)();let n=[],{items:r,...o}=e;if(r&&r[0].length>0)for(let e=0;e<r.length;e++)for(let t=0;t<r[e].length;t++)if(n[e]||(n[e]=[]),n[e][t]=Object.assign({},r[e][t]),"heading"!=r[e][t].type){const r=Object(c.a)();n[e][t].ref=r}return{ref:t,item:o,menus:n}}),[e]);Object(c.d)(()=>{const e=Ce(p,g);if(e.hasFocus){const[t,n,r]=p;e.isTop?(g[t].ref&&g[t].ref.current!==document.activeElement&&g[t].ref.current.focus(),h!==t&&u(-1)):g[t].menus[n][r].ref&&g[t].menus[n][r].ref.current!==document.activeElement&&g[t].menus[n][r].ref.current.focus()}else-1!==h&&u(-1)},[p,g]);const y=Object(c.f)(null);Object(c.d)(()=>{const e=e=>{y.current&&!y.current.contains(e.target)&&u(-1)};return document.addEventListener("mousedown",e),()=>{document.removeEventListener("mousedown",e)}},[y]);return Object(r.h)(J,{open:o,maxMobileHeight:i,injectStyles:s,breakpoint:l},Object(r.h)(q,He({},t>m?{onfocusout:e=>{e.currentTarget.contains(e.relatedTarget)||f([-1,-1,-1])}}:{},{onKeyDown:e=>{const t=Ce(p,g);if(t.hasFocus)switch(e.keyCode){case 37:e.preventDefault(),f(De(p,t,g));break;case 39:e.preventDefault(),f(Ne(p,t,g));break;case 38:e.preventDefault(),f(Re(p,t,g));break;case 40:if(t.isTop&&t.hasSubs&&h!=p[0])return void u(p[0]);e.preventDefault(),f(_e(p,t,g));break;case 9:if(e.shiftKey){if(t.isFirst)return!1;e.preventDefault(),f(De(p,t,g))}else{if(t.isLast)return!1;e.preventDefault(),f(Ne(p,t,g))}}},ref:y}),g.map((e,t)=>{const n=e.item,o=e.menus;return o&&o.length>0&&o[0].length>0?Object(r.h)(Ue,He({},n,{pIndex:t,setFocus:f,ref:e.ref,isOpen:h==t,setOpen:u,mega:o.length>2}),o.map((e,n)=>Object(r.h)(B,null,e.map((e,i)=>Object(r.h)(Le,{onFocus:()=>{b([t,n,i]),u(t)},ref:o[n][i].ref,type:e.hasOwnProperty("type")?e.type:void 0,color:e.hasOwnProperty("color")?e.color:void 0,class:e.hasOwnProperty("class")?e.class:void 0,href:e.hasOwnProperty("href")?e.href:void 0,tabIndex:"-1"},e.text))))):Object(r.h)(Le,{onFocus:()=>{f([t,-1,-1])},ref:e.ref,type:n.hasOwnProperty("type")?n.type:void 0,color:n.hasOwnProperty("color")?n.color:void 0,class:n.hasOwnProperty("class")?n.class:"",href:n.hasOwnProperty("href")?n.href:void 0},n.text)})),a.length>0&&Object(r.h)(W,null,a.map((e,t)=>{let n=e.color?e.color:"maroon";return Object(r.h)(O,He({href:e.href},{[n]:!0},{medium:!0}),e.text)})))};Me.propTypes={navTree:p.a.arrayOf(p.a.object),buttons:p.a.arrayOf(p.a.object),mobileOpen:p.a.bool,width:p.a.number,height:p.a.number,maxMobileHeight:p.a.number,injectStyles:p.a.bool,breakpoint:p.a.oneOf(["Lg","Xl"])},Me.defaultProps={navTree:[],mobileOpen:!1,width:1920,height:1080,maxMobileHeight:-1,buttons:[],injectStyles:!1};const Ce=(e,t)=>{const[n,r,o]=e;let i=!1,a=!1,s=!1,c=!1,l=!1;return-1==n&&-1==r&&-1==o?{hasFocus:i}:(i=!0,t[n].menus.length>0&&(s=!0),a=-1===r||-1===o,a&&n===t.length-1&&(c=!0),a&&0===n&&(l=!0),{hasFocus:i,isTop:a,hasSubs:s,isLast:c,isFirst:l})},De=(e,t,n)=>{const[r,o,i]=e;let a=e;return t.isTop?(a=void 0!==n[r-1]?[r-1,-1,-1]:[0,-1,-1],!1===Ae(a,n)?De(a,Ce(a,n),n):a):void 0!==n[r].menus[o-1]?n[r].menus[o-1][0].ref?[r,o-1,0]:[r,o-1,1]:[r,-1,-1]},Ne=(e,t,n)=>{const[r,o,i]=e;let a=e;return t.isTop?(a=void 0!==n[r+1]?[r+1,-1,-1]:[n.length-1,-1,-1],!1===Ae(a,n)?Ne(a,Ce(a,n),n):a):void 0!==n[r].menus[o+1]?n[r].menus[o+1][0].ref?[r,o+1,0]:[r,o+1,1]:[r,-1,-1]},Re=(e,t,n)=>{const[r,o,i]=e;let a=[],s=e;return t.hasSubs&&(a=n[r].menus),s=t.isTop?De(e,t,n):void 0!==a[o][i-1]?[r,o,i-1]:[r,-1,-1],!1===Ae(s,n)?Re(s,Ce(s,n),n):s},_e=(e,t,n)=>{const[r,o,i]=e;let a=[],s=e;return t.hasSubs&&(a=n[r].menus),s=t.isTop&&t.hasSubs?[r,0,0]:t.isTop?Ne(e,t,n):void 0!==a[o][i+1]?[r,o,i+1]:Ne(e,t,n),!1===Ae(s,n)?_e(s,Ce(s,n),n):s},Ae=(e,t)=>{const n=Ce(e,t);if(!n.hasFocus)return!1;if(n.isTop){if(t[e[0]].ref)return!0}else if(t[e[0]].menus[e[1]][e[2]].ref)return!0;return!1};function Ee(){return(Ee=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}const qe=({type:e,open:t,inputRef:n,mobile:o,...i})=>{switch(e){case"d7":return Object(r.h)("div",null,"Drupal 7");default:return Object(r.h)("form",{action:"https://search.asu.edu/search",method:"get",role:"search",class:t?"show-search-input":""},Object(r.h)("input",Ee({name:"q",type:"search"},n?{ref:n}:{},{"aria-labelledby":"asu-search-label"},o?{placeHolder:"Search ASU"}:{},{required:!0})),Object(r.h)("label",{class:"univeral-search",id:"asu-search-label"},"Search ASU"))}};qe.propTypes={type:p.a.string,open:p.a.bool,inputRef:p.a.oneOfType([p.a.func,p.a.shape({current:p.a.instanceOf(p.a.element)})]),mobile:p.a.bool},qe.defaultProps={};const We=({type:e,open:t,setOpen:n,mobile:o})=>{const i=Object(c.f)(null);return Object(r.h)(V,{onfocusin:()=>n(!0),onfocusout:e=>{i.current.value||e.currentTarget.contains(e.relatedTarget)||n(!1)},onClick:e=>{n(!0),i.current.focus()}},Object(r.h)(qe,{open:t,type:e,inputRef:i,mobile:o}))};We.propTypes={type:p.a.string,open:p.a.bool,setOpen:p.a.func,mobile:p.a.bool},We.defaultProps={open:!1};const Xe=({loggedIn:e,loginLink:t,logoutLink:n,userName:o,...i})=>Object(r.h)(ee,{class:i.class},e?Object(r.h)(r.b,null,o?Object(r.h)("span",{class:"name"},o):"",Object(r.h)("a",{class:"signout",href:n},"Sign Out")):Object(r.h)("a",{href:t},"Sign in"));function Be(){return(Be=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Xe.propTypes={class:p.a.string,loggedIn:p.a.bool.isRequired,loginLink:p.a.string,logoutLink:p.a.string,userName:p.a.string},Xe.defaultProps={logoutLink:"https://webapp4.asu.edu/myasu/Signout",loginLink:"https://weblogin.asu.edu/cgi-bin/login",loggedIn:!1};const Ke=({children:e,mobileOpen:t,logo:n,...o})=>Object(r.h)(fe,{mobileOpen:t},n,Object(r.h)(he,Be({},o,{mobileOpen:t})),Object(r.h)(ge,null,e));function Ge(){return(Ge=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Ke.propTypes={mobileOpen:p.a.bool,logo:p.a.node,children:p.a.node},Ke.defaultProps={mobileOpen:!1};const Je=Object(c.c)((e,t)=>Object(r.h)(re,Ge({ref:t},e)));function Ye(){return(Ye=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Je.propTypes={alt:p.a.string,src:p.a.string,mobileSrc:p.a.string,brandLink:p.a.string},Je.defaultProps={alt:"Arizona State University",src:"https://www.asu.edu/asuthemes/5.0/assets/arizona-state-university-logo-vertical.png",mobileSrc:"https://www.asu.edu/asuthemes/5.0/assets/arizona-state-university-logo.png",brandLink:"https://asu.edu"};const Qe=Object(c.c)(({children:e,baseUrl:t,animate:n,...o},i)=>{const[a,s]=Object(c.g)(!1);return Object(c.d)(()=>{if(!0!==n&&!1!==n){if(!1!==n){let e="/"==t?window.location.hostname:t;e.includes(window.location.hostname)||0!==e.indexOf("/")||(e=window.location.hostname+e),(e=>{const t=e||window.location.hostname,n=document.cookie.split("; ").find(e=>e.startsWith("title_loaded"));return!document.referrer.includes(t)&&!n&&(document.cookie="title_loaded=true;max-age=600",!0)})(e)&&s(!0)}}else s(n)},[a,n]),Object(r.h)(ie,Ye({ref:i},o,{class:a?"active":""}),e)});function Ve(){const e="undefined"!=typeof window,{innerWidth:t,innerHeight:n}=e?window:{innerWidth:1920,innerHeight:1080};return{width:t,height:n}}function Ze(){return(Ze=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t];for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r])}return e}).apply(this,arguments)}Qe.propTypes={baseUrl:p.a.string,parentOrg:p.a.string,parentOrgUrl:p.a.string,animate:p.a.bool},Qe.defaultProps={baseUrl:"/",parentOrgUrl:"/"};const et=({navTree:e,title:t,baseUrl:n,parentOrg:o,parentOrgUrl:i,logo:a,loggedIn:s,userName:l,loginLink:d,logoutLink:p,buttons:b,breakpoint:h,animateTitle:u,...f})=>{const[m,g]=Object(c.g)(!1),[O,y]=Object(c.g)(!1),[v,j]=Object(c.g)(-1),w="Xl"===h?"1260px":"992px",x=parseInt(w,10),{height:k,width:$}=function(){const[e,t]=Object(c.g)(Ve());return Object(c.d)(()=>{function e(){t(Ve())}return window.addEventListener("resize",e),()=>window.removeEventListener("resize",e)},[]),e}(),[z,P]=Object(c.g)(0),T=()=>{const e=window.pageYOffset;P(e)},S=parseInt("24px",10),L=Object(c.f)(null),F=Object(c.f)(null),I=Object(c.f)(null);Object(c.d)(()=>(window.addEventListener("scroll",T,{passive:!0}),()=>{window.removeEventListener("scroll",T)}),[]),Object(c.d)(()=>{$<x&&m&&window.setTimeout(()=>{const e=L.current.clientHeight,t=F.current.clientHeight,n=I.current.clientHeight;j(k-e-(t+n+S))},500)},[k,$,m]);const U=!0===u;return Object(r.h)(ye,{breakpoint:w,class:z>0||m&&$<x?"scrolled":""},Object(r.h)(je,Ze({open:m,ref:L},{searchOpen:O}),Object(r.h)(we,null,Object(r.h)("a",{href:"https://www.asu.edu/"},"ASU home"),Object(r.h)("a",{href:"https://my.asu.edu/"},"My ASU"),Object(r.h)("a",{href:"https://www.asu.edu/colleges/"},"Colleges and schools"),Object(r.h)(Xe,{loggedIn:s,loginLink:d,logoutLink:p,userName:l})),Object(r.h)(We,{open:O,setOpen:y,mobile:$<x})),Object(r.h)(Ke,{onClick:e=>{e.preventDefault(),g(e=>!e)},mobileOpen:m,logo:Object(r.h)(Je,Ze({},a,{ref:F}))},f.dangerouslyGenerateStub?Object(r.h)("div",{id:"asu-generated-stub"}):Object(r.h)(r.b,null,Object(r.h)(Qe,Ze({parentOrg:o,parentOrgUrl:i,baseUrl:n,animate:U},{ref:I}),t),Object(r.h)(Me,{navTree:e,mobileOpen:m,height:k,width:$,buttons:b,maxMobileHeight:v,breakpoint:h}))))};et.propTypes={navTree:p.a.arrayOf(p.a.object),logo:p.a.shape(Je.propTypes),title:Qe.propTypes.title,parentOrg:Qe.propTypes.parentOrg,parentOrgUrl:Qe.propTypes.parentOrgUrl,baseUrl:Qe.propTypes.baseUrl,loggedIn:Xe.propTypes.loggedIn,userName:Xe.propTypes.userName,loginLink:Xe.propTypes.loginLink,logoutLink:Xe.propTypes.logoutLink,buttons:p.a.arrayOf(p.a.object),breakpoint:p.a.oneOf(["Lg","Xl"]),animateTitle:p.a.bool},et.defaultProps={navTree:[],dangerouslyGenerateStub:!1,title:"",buttons:[],breakpoint:"Lg"};const tt=e=>Object(r.h)("div",{class:Object(l.b)(e.class,l.a`
          padding: 2rem;
          margin-bottom: 2rem;
          border-radius: 0.3rem;
          border: 1px solid #dee2e6;
        `)},e.children),nt=e=>Object(r.h)(tt,{class:e.class},e.children);nt.propTypes={class:p.a.string},nt.defaultProps={}}})}));
