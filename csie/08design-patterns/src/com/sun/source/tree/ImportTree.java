/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
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

package com.sun.source.tree;

/**
 * A tree node for an import statement.
 *
 * For example:
 * <pre>
 *   import <em>qualifiedIdentifier</em> ;
 *
 *   static import <em>qualifiedIdentifier</em> ;
 * </pre>
 *
 * @see "The Java Language Specification, 3rd ed, section 7.5"
 *
 * @author Peter von der Ah&eacute;
 * @author Jonathan Gibbons
 * @since 1.6
 */
public interface ImportTree extends Tree {
    boolean isStatic();
    /**
     * @return a qualified identifier ending in "*" if and only if
     * this is an import-on-demand.
     */
    Tree getQualifiedIdentifier();
}
