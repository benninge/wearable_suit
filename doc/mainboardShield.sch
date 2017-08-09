<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="maxim">
<description>&lt;b&gt;Maxim Components&lt;/b&gt;&lt;p&gt;

&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="DIL08">
<description>&lt;b&gt;Dual In Line Package&lt;/b&gt;</description>
<wire x1="5.08" y1="2.921" x2="-5.08" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.921" x2="5.08" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="5.08" y1="2.921" x2="5.08" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.921" x2="-5.08" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.921" x2="-5.08" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.016" x2="-5.08" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-5.334" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-3.556" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO08">
<description>&lt;b&gt;Small Outline Package&lt;/b&gt; SOIC 150 mil</description>
<wire x1="2.159" y1="1.9558" x2="-2.159" y2="1.9558" width="0.1524" layer="21"/>
<wire x1="2.159" y1="-1.9558" x2="2.54" y2="-1.5748" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.54" y1="1.5748" x2="-2.159" y2="1.9558" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.159" y1="1.9558" x2="2.54" y2="1.5748" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.54" y1="-1.5748" x2="-2.159" y2="-1.9558" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.159" y1="-1.9558" x2="2.159" y2="-1.9558" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.5748" x2="2.54" y2="1.5748" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.5748" x2="-2.54" y2="0.508" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.508" x2="-2.54" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.508" x2="-2.54" y2="-1.5748" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.508" x2="-2.54" y2="-0.508" width="0.1524" layer="21" curve="-180"/>
<wire x1="-2.54" y1="-1.6002" x2="2.54" y2="-1.6002" width="0.0508" layer="21"/>
<smd name="1" x="-1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="8" x="-1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="2" x="-0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="3" x="0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="7" x="-0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="6" x="0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="4" x="1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="5" x="1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<text x="3.937" y="-2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<text x="-2.921" y="-1.905" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="1.651" y1="1.9558" x2="2.159" y2="3.0988" layer="51"/>
<rectangle x1="-2.159" y1="-3.0988" x2="-1.651" y2="-1.9558" layer="51"/>
<rectangle x1="-0.889" y1="-3.0988" x2="-0.381" y2="-1.9558" layer="51"/>
<rectangle x1="0.381" y1="-3.0734" x2="0.889" y2="-1.9304" layer="51"/>
<rectangle x1="1.651" y1="-3.0988" x2="2.159" y2="-1.9558" layer="51"/>
<rectangle x1="0.381" y1="1.9558" x2="0.889" y2="3.0988" layer="51"/>
<rectangle x1="-0.889" y1="1.9558" x2="-0.381" y2="3.0988" layer="51"/>
<rectangle x1="-2.159" y1="1.9558" x2="-1.651" y2="3.0988" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MAX3468">
<wire x1="-10.16" y1="15.24" x2="17.78" y2="15.24" width="0.254" layer="94"/>
<wire x1="17.78" y1="15.24" x2="17.78" y2="-10.16" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="-10.16" y2="-10.16" width="0.254" layer="94"/>
<wire x1="17.653" y1="5.08" x2="5.08" y2="5.08" width="0.127" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-2.54" width="0.127" layer="94"/>
<wire x1="7.62" y1="0" x2="17.653" y2="0" width="0.127" layer="94"/>
<wire x1="5.08" y1="7.62" x2="5.08" y2="5.08" width="0.127" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="-10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="-10.16" y1="10.16" x2="-10.16" y2="15.24" width="0.254" layer="94"/>
<wire x1="2.667" y1="13.97" x2="2.667" y2="12.7" width="0.127" layer="94"/>
<wire x1="2.667" y1="12.7" x2="2.667" y2="6.35" width="0.127" layer="94"/>
<wire x1="2.667" y1="6.35" x2="-3.937" y2="10.16" width="0.127" layer="94"/>
<wire x1="-3.937" y1="10.16" x2="2.667" y2="13.97" width="0.127" layer="94"/>
<wire x1="-4.064" y1="5.08" x2="-0.762" y2="5.08" width="0.127" layer="94"/>
<wire x1="-0.762" y1="5.08" x2="-0.762" y2="6.985" width="0.127" layer="94"/>
<wire x1="2.667" y1="12.7" x2="7.62" y2="12.7" width="0.127" layer="94"/>
<wire x1="7.62" y1="12.7" x2="7.62" y2="0" width="0.127" layer="94"/>
<wire x1="5.08" y1="7.62" x2="4.064" y2="7.62" width="0.127" layer="94"/>
<wire x1="-10.16" y1="10.16" x2="-8.382" y2="10.16" width="0.127" layer="94"/>
<wire x1="-4.445" y1="10.16" x2="-3.937" y2="10.16" width="0.127" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="-8.382" y2="5.08" width="0.127" layer="94"/>
<wire x1="-10.16" y1="5.08" x2="-10.16" y2="0" width="0.254" layer="94"/>
<wire x1="-10.16" y1="0" x2="-10.16" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-5.08" x2="-10.16" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-3.937" y1="-8.89" x2="-3.937" y2="-5.08" width="0.127" layer="94"/>
<wire x1="-3.937" y1="-5.08" x2="-3.937" y2="-1.27" width="0.127" layer="94"/>
<wire x1="-3.937" y1="-1.27" x2="3.048" y2="-5.08" width="0.127" layer="94"/>
<wire x1="3.048" y1="-5.08" x2="-3.937" y2="-8.89" width="0.127" layer="94"/>
<wire x1="-4.572" y1="0" x2="-2.032" y2="0" width="0.127" layer="94"/>
<wire x1="-2.032" y1="0" x2="-2.032" y2="-2.286" width="0.127" layer="94"/>
<wire x1="-10.16" y1="-5.08" x2="-8.509" y2="-5.08" width="0.127" layer="94"/>
<wire x1="-4.826" y1="-5.08" x2="-3.937" y2="-5.08" width="0.127" layer="94"/>
<wire x1="-10.16" y1="0" x2="-8.509" y2="0" width="0.127" layer="94"/>
<wire x1="-1.524" y1="-7.62" x2="7.62" y2="-7.62" width="0.127" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="7.62" y2="0" width="0.127" layer="94"/>
<wire x1="0.381" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="94"/>
<circle x="7.62" y="0" radius="0.3592" width="0" layer="94"/>
<circle x="5.08" y="5.08" radius="0.3592" width="0" layer="94"/>
<circle x="-0.762" y="7.62" radius="0.635" width="0.127" layer="94"/>
<circle x="3.302" y="7.62" radius="0.635" width="0.127" layer="94"/>
<circle x="-0.381" y="-2.54" radius="0.635" width="0.127" layer="94"/>
<text x="15.24" y="0.381" size="1.524" layer="95">A</text>
<text x="15.24" y="5.461" size="1.524" layer="95">B</text>
<text x="-7.62" y="16.51" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<pin name="B" x="20.32" y="5.08" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="A" x="20.32" y="0" visible="pad" length="short" direction="pas" rot="R180"/>
<pin name="GND" x="20.32" y="-7.62" length="short" direction="pwr" rot="R180"/>
<pin name="VCC" x="20.32" y="12.7" length="short" direction="pwr" rot="R180"/>
<pin name="RO" x="-12.7" y="10.16" length="short" direction="out"/>
<pin name="RE/" x="-12.7" y="5.08" length="short" direction="in"/>
<pin name="DE" x="-12.7" y="0" length="short" direction="in"/>
<pin name="DI" x="-12.7" y="-5.08" length="short" direction="in"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MAX34*" prefix="IC">
<description>&lt;b&gt;+5V, Fail-Safe, 40Mbps, Profibus RS-485/RS-422 Transceivers&lt;/b&gt;&lt;p&gt;
Source: MAX3465-MAX3469.pdf</description>
<gates>
<gate name="G$1" symbol="MAX3468" x="0" y="0"/>
</gates>
<devices>
<device name="PA" package="DIL08">
<connects>
<connect gate="G$1" pin="A" pad="6"/>
<connect gate="G$1" pin="B" pad="7"/>
<connect gate="G$1" pin="DE" pad="3"/>
<connect gate="G$1" pin="DI" pad="4"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="RE/" pad="2"/>
<connect gate="G$1" pin="RO" pad="1"/>
<connect gate="G$1" pin="VCC" pad="8"/>
</connects>
<technologies>
<technology name="68C">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="68E">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="MAX3468EPA+" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="78M5804" constant="no"/>
</technology>
<technology name="69C">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="69E">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="SA" package="SO08">
<connects>
<connect gate="G$1" pin="A" pad="6"/>
<connect gate="G$1" pin="B" pad="7"/>
<connect gate="G$1" pin="DE" pad="3"/>
<connect gate="G$1" pin="DI" pad="4"/>
<connect gate="G$1" pin="GND" pad="5"/>
<connect gate="G$1" pin="RE/" pad="2"/>
<connect gate="G$1" pin="RO" pad="1"/>
<connect gate="G$1" pin="VCC" pad="8"/>
</connects>
<technologies>
<technology name="68C">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="MAX3468CSA+" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="76K6721" constant="no"/>
</technology>
<technology name="68E">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="MAX3468ESA+T" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="76K6724" constant="no"/>
</technology>
<technology name="69C">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="MAX3469CSA+" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="05M8548" constant="no"/>
</technology>
<technology name="69E">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="MAX3469ESA+" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="67K5012" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="burr-brown">
<description>&lt;b&gt;Burr-Brown Components&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="SOT223">
<description>&lt;b&gt;Smal Outline Transistor&lt;/b&gt;</description>
<wire x1="-3.124" y1="1.731" x2="-3.124" y2="-1.729" width="0.1524" layer="21"/>
<wire x1="3.124" y1="-1.729" x2="3.124" y2="1.731" width="0.1524" layer="21"/>
<wire x1="-3.124" y1="1.731" x2="3.124" y2="1.731" width="0.1524" layer="21"/>
<wire x1="3.124" y1="-1.729" x2="-3.124" y2="-1.729" width="0.1524" layer="21"/>
<smd name="1" x="-2.2606" y="-3.1496" dx="1.4986" dy="2.0066" layer="1"/>
<smd name="2" x="0.0254" y="-3.1496" dx="1.4986" dy="2.0066" layer="1"/>
<smd name="3" x="2.3114" y="-3.1496" dx="1.4986" dy="2.0066" layer="1"/>
<smd name="4" x="0" y="3.1496" dx="3.81" dy="2.0066" layer="1"/>
<text x="-2.54" y="4.318" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.794" y="-5.842" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.524" y1="1.778" x2="1.524" y2="3.302" layer="51"/>
<rectangle x1="-2.667" y1="-3.302" x2="-1.905" y2="-1.778" layer="51"/>
<rectangle x1="1.905" y1="-3.302" x2="2.667" y2="-1.778" layer="51"/>
<rectangle x1="-0.381" y1="-3.302" x2="0.381" y2="-1.778" layer="51"/>
</package>
<package name="DD-3">
<description>&lt;b&gt;DPAC&lt;/b&gt;</description>
<wire x1="-5.398" y1="-4.445" x2="-5.084" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-5.084" y1="-4.445" x2="5.076" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="5.076" y1="-4.445" x2="5.398" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="5.398" y1="-4.445" x2="5.398" y2="4.128" width="0.1524" layer="21"/>
<wire x1="5.398" y1="4.128" x2="-5.398" y2="4.128" width="0.1524" layer="21"/>
<wire x1="-5.398" y1="4.128" x2="-5.398" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-5.084" y1="3.81" x2="5.076" y2="3.81" width="0.1524" layer="21"/>
<wire x1="5.076" y1="3.81" x2="5.076" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-5.084" y1="-4.445" x2="-5.084" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-5.398" y1="4.128" x2="-5.084" y2="3.81" width="0.1524" layer="21"/>
<wire x1="5.398" y1="4.128" x2="5.076" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-5.398" y1="4.128" x2="-5.398" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-5.398" y1="5.08" x2="-4.445" y2="5.715" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="5.715" x2="4.445" y2="5.715" width="0.1524" layer="21"/>
<wire x1="4.445" y1="5.715" x2="5.398" y2="5.08" width="0.1524" layer="21"/>
<wire x1="5.398" y1="5.08" x2="5.398" y2="4.128" width="0.1524" layer="21"/>
<smd name="1" x="-2.54" y="-7.9375" dx="1.27" dy="5.08" layer="1"/>
<smd name="2" x="0" y="-7.9375" dx="1.27" dy="5.08" layer="1"/>
<smd name="3" x="2.54" y="-7.9375" dx="1.27" dy="5.08" layer="1"/>
<text x="-3.81" y="-10.795" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-2.54" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.175" y1="-9.525" x2="-1.905" y2="-4.445" layer="51"/>
<rectangle x1="-0.635" y1="-9.525" x2="0.635" y2="-4.445" layer="51"/>
<rectangle x1="1.905" y1="-9.525" x2="3.175" y2="-4.445" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="REG1118">
<wire x1="-7.62" y1="-7.62" x2="7.62" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="7.62" y2="5.08" width="0.4064" layer="94"/>
<wire x1="7.62" y1="5.08" x2="-7.62" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="5.08" x2="-7.62" y2="-7.62" width="0.4064" layer="94"/>
<text x="-7.62" y="5.715" size="1.778" layer="95" ratio="10">&gt;NAME</text>
<text x="-5.08" y="2.54" size="1.778" layer="96" ratio="10">&gt;VALUE</text>
<pin name="VIN" x="-12.7" y="0" length="middle" direction="in"/>
<pin name="VOUT" x="12.7" y="0" length="middle" direction="out" rot="R180"/>
<pin name="GND" x="0" y="-12.7" length="middle" direction="pwr" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="REG1117" prefix="IC">
<description>&lt;b&gt;800mA and 1A Low Dropout (LDO) Positive Regulator&lt;/b&gt;&lt;p&gt;
1.8V, 2.5V, 2.85V, 3.3V, 5V, and Adj</description>
<gates>
<gate name="G$1" symbol="REG1118" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT223">
<connects>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="VIN" pad="3"/>
<connect gate="G$1" pin="VOUT" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="REG1117" constant="no"/>
<attribute name="OC_FARNELL" value="1097566" constant="no"/>
<attribute name="OC_NEWARK" value="14P6981" constant="no"/>
</technology>
</technologies>
</device>
<device name="F" package="DD-3">
<connects>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="VIN" pad="3"/>
<connect gate="G$1" pin="VOUT" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="TEXAS INSTRUMENTS" constant="no"/>
<attribute name="MPN" value="REG1117FAKTTT" constant="no"/>
<attribute name="OC_FARNELL" value="1296120" constant="no"/>
<attribute name="OC_NEWARK" value="87H2562" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="+3V3">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+3V3" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="VCC">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="+5V">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="+5V" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="+3V3" prefix="+3V3">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="+3V3" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="VCC" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="VCC" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="+5V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="+5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="mbLib">
<packages>
<package name="LEDSTRIPDUMMY">
<smd name="P$1" x="0" y="1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="0" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="0" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="LEDDISPLAYDUMMY">
<smd name="P$1" x="1.27" y="1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="1.27" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="1.27" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="-1.27" y="0" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="ADAFRUITMIC">
<smd name="P$1" x="0" y="3.81" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="0" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="0" y="1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="0" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$5" x="0" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="STM32F411E-DISCO">
<smd name="P$1" x="2.54" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="2.54" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="2.54" y="3.81" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="2.54" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$5" x="2.54" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$6" x="2.54" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$7" x="-1.27" y="6.35" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$8" x="-1.27" y="5.08" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$9" x="-1.27" y="3.81" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$10" x="-1.27" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$11" x="-1.27" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$12" x="-1.27" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$13" x="-1.27" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$14" x="2.54" y="-2.54" dx="1.27" dy="0.635" layer="1"/>
</package>
<package name="BUS">
<smd name="P$1" x="0" y="2.54" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$2" x="0" y="1.27" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$3" x="0" y="0" dx="1.27" dy="0.635" layer="1"/>
<smd name="P$4" x="0" y="-1.27" dx="1.27" dy="0.635" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="LEDSTRIP">
<pin name="VCC" x="7.62" y="5.08" length="middle" rot="R180"/>
<pin name="D_IN" x="7.62" y="0" length="middle" rot="R180"/>
<pin name="GND" x="7.62" y="-5.08" length="middle" rot="R180"/>
<wire x1="2.54" y1="7.62" x2="-7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="2.54" y2="-7.62" width="0.254" layer="94"/>
<wire x1="2.54" y1="-7.62" x2="2.54" y2="7.62" width="0.254" layer="94"/>
</symbol>
<symbol name="LEDDISPLAY">
<pin name="VCC" x="10.16" y="5.08" length="middle" rot="R180"/>
<pin name="D_IN" x="10.16" y="0" length="middle" rot="R180"/>
<pin name="GND" x="10.16" y="-5.08" length="middle" rot="R180"/>
<pin name="D_OUT" x="-17.78" y="0" length="middle"/>
<wire x1="5.08" y1="7.62" x2="-12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="-12.7" y1="7.62" x2="-12.7" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="-7.62" x2="5.08" y2="7.62" width="0.254" layer="94"/>
</symbol>
<symbol name="ADAFRUITMIC">
<pin name="VDD" x="7.62" y="10.16" length="middle" rot="R180"/>
<pin name="OUT" x="7.62" y="5.08" length="middle" rot="R180"/>
<pin name="AR" x="7.62" y="0" length="middle" rot="R180"/>
<pin name="GAIN" x="7.62" y="-5.08" length="middle" rot="R180"/>
<pin name="GND" x="7.62" y="-10.16" length="middle" rot="R180"/>
<wire x1="2.54" y1="12.7" x2="-7.62" y2="12.7" width="0.254" layer="94"/>
<wire x1="-7.62" y1="12.7" x2="-7.62" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-12.7" x2="2.54" y2="-12.7" width="0.254" layer="94"/>
<wire x1="2.54" y1="-12.7" x2="2.54" y2="12.7" width="0.254" layer="94"/>
</symbol>
<symbol name="STM32F411E-DISCO">
<pin name="GND" x="12.7" y="-12.7" length="middle" rot="R180"/>
<pin name="A7" x="12.7" y="15.24" length="middle" rot="R180"/>
<pin name="B0" x="12.7" y="10.16" length="middle" rot="R180"/>
<pin name="B1" x="12.7" y="5.08" length="middle" rot="R180"/>
<pin name="A6" x="12.7" y="20.32" length="middle" rot="R180"/>
<pin name="3V3" x="12.7" y="-7.62" length="middle" rot="R180"/>
<pin name="B7" x="-12.7" y="20.32" length="middle"/>
<pin name="B4" x="-12.7" y="15.24" length="middle"/>
<pin name="B5" x="-12.7" y="10.16" length="middle"/>
<pin name="B6" x="-12.7" y="5.08" length="middle"/>
<pin name="C1" x="-12.7" y="-7.62" length="middle"/>
<pin name="C2" x="-12.7" y="-12.7" length="middle"/>
<pin name="C0" x="-12.7" y="-2.54" length="middle"/>
<wire x1="-7.62" y1="22.86" x2="7.62" y2="22.86" width="0.254" layer="94"/>
<wire x1="7.62" y1="22.86" x2="7.62" y2="-15.24" width="0.254" layer="94"/>
<wire x1="7.62" y1="-15.24" x2="-7.62" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-15.24" x2="-7.62" y2="22.86" width="0.254" layer="94"/>
<pin name="5V" x="12.7" y="-2.54" length="middle" rot="R180"/>
</symbol>
<symbol name="BUS">
<pin name="VCC" x="7.62" y="7.62" length="middle" rot="R180"/>
<pin name="A" x="7.62" y="2.54" length="middle" rot="R180"/>
<pin name="B" x="7.62" y="-2.54" length="middle" rot="R180"/>
<pin name="GND" x="7.62" y="-7.62" length="middle" rot="R180"/>
<wire x1="2.54" y1="10.16" x2="-5.08" y2="10.16" width="0.254" layer="94"/>
<wire x1="-5.08" y1="10.16" x2="-5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-10.16" x2="2.54" y2="-10.16" width="0.254" layer="94"/>
<wire x1="2.54" y1="-10.16" x2="2.54" y2="10.16" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LEDSTRIP">
<gates>
<gate name="G$1" symbol="LEDSTRIP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LEDSTRIPDUMMY">
<connects>
<connect gate="G$1" pin="D_IN" pad="P$1"/>
<connect gate="G$1" pin="GND" pad="P$2"/>
<connect gate="G$1" pin="VCC" pad="P$3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LEDDISPLAY">
<gates>
<gate name="G$1" symbol="LEDDISPLAY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LEDDISPLAYDUMMY">
<connects>
<connect gate="G$1" pin="D_IN" pad="P$1"/>
<connect gate="G$1" pin="D_OUT" pad="P$2"/>
<connect gate="G$1" pin="GND" pad="P$3"/>
<connect gate="G$1" pin="VCC" pad="P$4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ADAFRUITMIC">
<gates>
<gate name="G$1" symbol="ADAFRUITMIC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ADAFRUITMIC">
<connects>
<connect gate="G$1" pin="AR" pad="P$1"/>
<connect gate="G$1" pin="GAIN" pad="P$2"/>
<connect gate="G$1" pin="GND" pad="P$3"/>
<connect gate="G$1" pin="OUT" pad="P$4"/>
<connect gate="G$1" pin="VDD" pad="P$5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STM32F411E-DISCO">
<gates>
<gate name="G$1" symbol="STM32F411E-DISCO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="STM32F411E-DISCO">
<connects>
<connect gate="G$1" pin="3V3" pad="P$1"/>
<connect gate="G$1" pin="5V" pad="P$14"/>
<connect gate="G$1" pin="A6" pad="P$2"/>
<connect gate="G$1" pin="A7" pad="P$3"/>
<connect gate="G$1" pin="B0" pad="P$4"/>
<connect gate="G$1" pin="B1" pad="P$5"/>
<connect gate="G$1" pin="B4" pad="P$6"/>
<connect gate="G$1" pin="B5" pad="P$7"/>
<connect gate="G$1" pin="B6" pad="P$8"/>
<connect gate="G$1" pin="B7" pad="P$9"/>
<connect gate="G$1" pin="C0" pad="P$10"/>
<connect gate="G$1" pin="C1" pad="P$11"/>
<connect gate="G$1" pin="C2" pad="P$12"/>
<connect gate="G$1" pin="GND" pad="P$13"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BUS">
<gates>
<gate name="G$1" symbol="BUS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BUS">
<connects>
<connect gate="G$1" pin="A" pad="P$1"/>
<connect gate="G$1" pin="B" pad="P$2"/>
<connect gate="G$1" pin="GND" pad="P$3"/>
<connect gate="G$1" pin="VCC" pad="P$4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="maxim" deviceset="MAX34*" device="PA" technology="69E" value="RS485 TRX"/>
<part name="IC2" library="burr-brown" deviceset="REG1117" device="F" value="5V LDO"/>
<part name="+3V1" library="supply1" deviceset="+3V3" device=""/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
<part name="P+1" library="supply1" deviceset="VCC" device=""/>
<part name="LEDSTRIP" library="mbLib" deviceset="LEDSTRIP" device=""/>
<part name="U$2" library="mbLib" deviceset="LEDSTRIP" device=""/>
<part name="U$3" library="mbLib" deviceset="LEDSTRIP" device=""/>
<part name="U$4" library="mbLib" deviceset="LEDSTRIP" device=""/>
<part name="U$1" library="mbLib" deviceset="LEDDISPLAY" device=""/>
<part name="U$5" library="mbLib" deviceset="ADAFRUITMIC" device=""/>
<part name="STM32" library="mbLib" deviceset="STM32F411E-DISCO" device=""/>
<part name="P+2" library="supply1" deviceset="+5V" device=""/>
<part name="P+3" library="supply1" deviceset="VCC" device=""/>
<part name="GND2" library="supply1" deviceset="GND" device=""/>
<part name="P+4" library="supply1" deviceset="VCC" device=""/>
<part name="P+5" library="supply1" deviceset="VCC" device=""/>
<part name="GND3" library="supply1" deviceset="GND" device=""/>
<part name="GND4" library="supply1" deviceset="GND" device=""/>
<part name="P+6" library="supply1" deviceset="VCC" device=""/>
<part name="GND5" library="supply1" deviceset="GND" device=""/>
<part name="GND6" library="supply1" deviceset="GND" device=""/>
<part name="+3V2" library="supply1" deviceset="+3V3" device=""/>
<part name="GND7" library="supply1" deviceset="GND" device=""/>
<part name="U$6" library="mbLib" deviceset="BUS" device=""/>
<part name="GND8" library="supply1" deviceset="GND" device=""/>
<part name="P+7" library="supply1" deviceset="VCC" device=""/>
<part name="P+8" library="supply1" deviceset="+5V" device=""/>
<part name="GND9" library="supply1" deviceset="GND" device=""/>
<part name="P+9" library="supply1" deviceset="+5V" device=""/>
<part name="GND10" library="supply1" deviceset="GND" device=""/>
<part name="P+10" library="supply1" deviceset="VCC" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="63.5" y="60.96" rot="MR0"/>
<instance part="IC2" gate="G$1" x="68.58" y="-10.16"/>
<instance part="+3V1" gate="G$1" x="119.38" y="50.8"/>
<instance part="GND1" gate="1" x="134.62" y="60.96"/>
<instance part="P+1" gate="VCC" x="134.62" y="83.82"/>
<instance part="LEDSTRIP" gate="G$1" x="144.78" y="71.12" rot="MR0"/>
<instance part="U$2" gate="G$1" x="144.78" y="40.64" rot="MR0"/>
<instance part="U$3" gate="G$1" x="144.78" y="-20.32" rot="MR0"/>
<instance part="U$4" gate="G$1" x="144.78" y="10.16" rot="MR0"/>
<instance part="U$1" gate="G$1" x="116.84" y="-20.32" rot="MR0"/>
<instance part="U$5" gate="G$1" x="25.4" y="22.86"/>
<instance part="STM32" gate="G$1" x="91.44" y="50.8"/>
<instance part="P+2" gate="1" x="111.76" y="53.34"/>
<instance part="P+3" gate="VCC" x="134.62" y="53.34"/>
<instance part="GND2" gate="1" x="134.62" y="30.48"/>
<instance part="P+4" gate="VCC" x="134.62" y="22.86"/>
<instance part="P+5" gate="VCC" x="104.14" y="-7.62"/>
<instance part="GND3" gate="1" x="134.62" y="0"/>
<instance part="GND4" gate="1" x="104.14" y="-30.48"/>
<instance part="P+6" gate="VCC" x="134.62" y="-7.62"/>
<instance part="GND5" gate="1" x="134.62" y="-30.48"/>
<instance part="GND6" gate="1" x="111.76" y="33.02"/>
<instance part="+3V2" gate="G$1" x="40.64" y="81.28"/>
<instance part="GND7" gate="1" x="40.64" y="48.26"/>
<instance part="U$6" gate="G$1" x="22.86" y="63.5" rot="MR180"/>
<instance part="GND8" gate="1" x="33.02" y="76.2" rot="R180"/>
<instance part="P+7" gate="VCC" x="33.02" y="50.8" rot="R180"/>
<instance part="P+8" gate="1" x="38.1" y="40.64"/>
<instance part="GND9" gate="1" x="35.56" y="5.08"/>
<instance part="P+9" gate="1" x="86.36" y="-2.54"/>
<instance part="GND10" gate="1" x="68.58" y="-30.48"/>
<instance part="P+10" gate="VCC" x="50.8" y="-2.54"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="LEDSTRIP" gate="G$1" pin="D_IN"/>
<pinref part="STM32" gate="G$1" pin="A6"/>
<wire x1="137.16" y1="71.12" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="D_OUT"/>
<pinref part="U$3" gate="G$1" pin="D_IN"/>
<wire x1="134.62" y1="-20.32" x2="137.16" y2="-20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="LEDSTRIP" gate="G$1" pin="VCC"/>
<pinref part="P+1" gate="VCC" pin="VCC"/>
<wire x1="137.16" y1="76.2" x2="134.62" y2="76.2" width="0.1524" layer="91"/>
<wire x1="134.62" y1="76.2" x2="134.62" y2="81.28" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="VCC"/>
<pinref part="P+3" gate="VCC" pin="VCC"/>
<wire x1="137.16" y1="45.72" x2="134.62" y2="45.72" width="0.1524" layer="91"/>
<wire x1="134.62" y1="45.72" x2="134.62" y2="50.8" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="VCC"/>
<pinref part="P+4" gate="VCC" pin="VCC"/>
<wire x1="137.16" y1="15.24" x2="134.62" y2="15.24" width="0.1524" layer="91"/>
<wire x1="134.62" y1="15.24" x2="134.62" y2="20.32" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="VCC"/>
<pinref part="P+5" gate="VCC" pin="VCC"/>
<wire x1="106.68" y1="-15.24" x2="104.14" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-15.24" x2="104.14" y2="-10.16" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="VCC"/>
<pinref part="P+6" gate="VCC" pin="VCC"/>
<wire x1="137.16" y1="-15.24" x2="134.62" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="134.62" y1="-15.24" x2="134.62" y2="-10.16" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$6" gate="G$1" pin="VCC"/>
<pinref part="P+7" gate="VCC" pin="VCC"/>
<wire x1="30.48" y1="55.88" x2="33.02" y2="55.88" width="0.1524" layer="91"/>
<wire x1="33.02" y1="55.88" x2="33.02" y2="53.34" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="VIN"/>
<pinref part="P+10" gate="VCC" pin="VCC"/>
<wire x1="55.88" y1="-10.16" x2="50.8" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="50.8" y1="-10.16" x2="50.8" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="LEDSTRIP" gate="G$1" pin="GND"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="137.16" y1="66.04" x2="134.62" y2="66.04" width="0.1524" layer="91"/>
<wire x1="134.62" y1="66.04" x2="134.62" y2="63.5" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND"/>
<pinref part="GND2" gate="1" pin="GND"/>
<wire x1="137.16" y1="35.56" x2="134.62" y2="35.56" width="0.1524" layer="91"/>
<wire x1="134.62" y1="35.56" x2="134.62" y2="33.02" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="GND"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="137.16" y1="5.08" x2="134.62" y2="5.08" width="0.1524" layer="91"/>
<wire x1="134.62" y1="5.08" x2="134.62" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="106.68" y1="-25.4" x2="104.14" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-25.4" x2="104.14" y2="-27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="GND"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="137.16" y1="-25.4" x2="134.62" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="134.62" y1="-25.4" x2="134.62" y2="-27.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="STM32" gate="G$1" pin="GND"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="104.14" y1="38.1" x2="111.76" y2="38.1" width="0.1524" layer="91"/>
<wire x1="111.76" y1="38.1" x2="111.76" y2="35.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$6" gate="G$1" pin="GND"/>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="30.48" y1="71.12" x2="33.02" y2="71.12" width="0.1524" layer="91"/>
<wire x1="33.02" y1="71.12" x2="33.02" y2="73.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="GND"/>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="43.18" y1="53.34" x2="40.64" y2="53.34" width="0.1524" layer="91"/>
<wire x1="40.64" y1="53.34" x2="40.64" y2="50.8" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="35.56" y1="7.62" x2="35.56" y2="12.7" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="GND"/>
<wire x1="35.56" y1="12.7" x2="33.02" y2="12.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND10" gate="1" pin="GND"/>
<pinref part="IC2" gate="G$1" pin="GND"/>
<wire x1="68.58" y1="-27.94" x2="68.58" y2="-22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="D_IN"/>
<wire x1="137.16" y1="40.64" x2="127" y2="40.64" width="0.1524" layer="91"/>
<wire x1="127" y1="40.64" x2="127" y2="66.04" width="0.1524" layer="91"/>
<pinref part="STM32" gate="G$1" pin="A7"/>
<wire x1="127" y1="66.04" x2="104.14" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="D_IN"/>
<wire x1="137.16" y1="10.16" x2="124.46" y2="10.16" width="0.1524" layer="91"/>
<wire x1="124.46" y1="10.16" x2="124.46" y2="60.96" width="0.1524" layer="91"/>
<pinref part="STM32" gate="G$1" pin="B0"/>
<wire x1="124.46" y1="60.96" x2="104.14" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="B1"/>
<wire x1="121.92" y1="55.88" x2="104.14" y2="55.88" width="0.1524" layer="91"/>
<wire x1="121.92" y1="55.88" x2="121.92" y2="10.16" width="0.1524" layer="91"/>
<wire x1="121.92" y1="10.16" x2="96.52" y2="10.16" width="0.1524" layer="91"/>
<wire x1="96.52" y1="10.16" x2="96.52" y2="-20.32" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="D_IN"/>
<wire x1="96.52" y1="-20.32" x2="106.68" y2="-20.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="5V"/>
<pinref part="P+2" gate="1" pin="+5V"/>
<wire x1="104.14" y1="48.26" x2="111.76" y2="48.26" width="0.1524" layer="91"/>
<wire x1="111.76" y1="48.26" x2="111.76" y2="50.8" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$5" gate="G$1" pin="VDD"/>
<pinref part="P+8" gate="1" pin="+5V"/>
<wire x1="33.02" y1="33.02" x2="38.1" y2="33.02" width="0.1524" layer="91"/>
<wire x1="38.1" y1="33.02" x2="38.1" y2="38.1" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC2" gate="G$1" pin="VOUT"/>
<pinref part="P+9" gate="1" pin="+5V"/>
<wire x1="81.28" y1="-10.16" x2="86.36" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="86.36" y1="-10.16" x2="86.36" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+3V3" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="3V3"/>
<pinref part="+3V1" gate="G$1" pin="+3V3"/>
<wire x1="104.14" y1="43.18" x2="119.38" y2="43.18" width="0.1524" layer="91"/>
<wire x1="119.38" y1="43.18" x2="119.38" y2="48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="IC1" gate="G$1" pin="VCC"/>
<pinref part="+3V2" gate="G$1" pin="+3V3"/>
<wire x1="43.18" y1="73.66" x2="40.64" y2="73.66" width="0.1524" layer="91"/>
<wire x1="40.64" y1="73.66" x2="40.64" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="RO"/>
<pinref part="STM32" gate="G$1" pin="B7"/>
<wire x1="76.2" y1="71.12" x2="78.74" y2="71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="B4"/>
<pinref part="IC1" gate="G$1" pin="RE/"/>
<wire x1="78.74" y1="66.04" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="DE"/>
<pinref part="STM32" gate="G$1" pin="B5"/>
<wire x1="76.2" y1="60.96" x2="78.74" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="B6"/>
<pinref part="IC1" gate="G$1" pin="DI"/>
<wire x1="78.74" y1="55.88" x2="76.2" y2="55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="B"/>
<pinref part="IC1" gate="G$1" pin="B"/>
<wire x1="30.48" y1="66.04" x2="43.18" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="IC1" gate="G$1" pin="A"/>
<pinref part="U$6" gate="G$1" pin="A"/>
<wire x1="43.18" y1="60.96" x2="30.48" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="C2"/>
<wire x1="78.74" y1="38.1" x2="76.2" y2="38.1" width="0.1524" layer="91"/>
<wire x1="76.2" y1="38.1" x2="76.2" y2="17.78" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="GAIN"/>
<wire x1="76.2" y1="17.78" x2="33.02" y2="17.78" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="STM32" gate="G$1" pin="C1"/>
<wire x1="78.74" y1="43.18" x2="73.66" y2="43.18" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="AR"/>
<wire x1="73.66" y1="43.18" x2="73.66" y2="22.86" width="0.1524" layer="91"/>
<wire x1="73.66" y1="22.86" x2="33.02" y2="22.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U$5" gate="G$1" pin="OUT"/>
<wire x1="33.02" y1="27.94" x2="71.12" y2="27.94" width="0.1524" layer="91"/>
<wire x1="71.12" y1="27.94" x2="71.12" y2="48.26" width="0.1524" layer="91"/>
<pinref part="STM32" gate="G$1" pin="C0"/>
<wire x1="71.12" y1="48.26" x2="78.74" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
