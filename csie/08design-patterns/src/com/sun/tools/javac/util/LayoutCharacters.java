/*
 * Copyright 1999-2005 Sun Microsystems, Inc.  All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

package com.sun.tools.javac.util;

/** An interface containing layout character constants used in Java
 *  programs.
 *
 *  <p><b>This is NOT part of any API supported by Sun Microsystems.  If
 *  you write code that depends on this, you do so at your own risk.
 *  This code and its internal interfaces are subject to change or
 *  deletion without notice.</b>
 */
public interface LayoutCharacters {

    /** Tabulator column increment.
     */
    final static int TabInc = 8;

    /** Tabulator character.
     */
    final static byte TAB   = 0x8;

    /** Line feed character.
     */
    final static byte LF    = 0xA;

    /** Form feed character.
     */
    final static byte FF    = 0xC;

    /** Carriage return character.
     */
    final static byte CR    = 0xD;

    /** End of input character.  Used as a sentinel to denote the
     *  character one beyond the last defined character in a
     *  source file.
     */
    final static byte EOI   = 0x1A;
}
