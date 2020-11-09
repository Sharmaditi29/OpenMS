// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2020.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Timo Sachsenberg $
// $Authors: Timo Sachsenberg $
// --------------------------------------------------------------------------

#pragma once

#include <QtWidgets>


#include <OpenMS/VISUAL/LayerData.h>

class QLineEdit;
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;

namespace OpenMS
{
  /**
    @brief Hierarchical visualization and selection of spectra.

    @ingroup PlotWidgets
  */
  class SpectraTreeTab :
    public QWidget
  {
    Q_OBJECT
public:
    /// Constructor
    SpectraTreeTab(QWidget * parent = nullptr);
    /// Destructor
    ~SpectraTreeTab() = default;

    /// refresh the table using data from @p cl
    void updateEntries(const LayerData & cl);
    /// remove all visible data
    void clear();

    /// Return a copy of the currently selected spectrum/chrom (for drag'n'drop to new window)
    /// and store it either as Spectrum or Chromatogram in @p exp (all other data is cleared)
    /// If no spectrum/chrom is selected, false is returned and @p exp is empty
    bool getSelectedScan(MSExperiment& exp) const;

signals:
    void spectrumSelected(int);
    void spectrumSelected(std::vector<int> indices);
    void spectrumDoubleClicked(int);
    void spectrumDoubleClicked(std::vector<int> indices);
    void showSpectrumAs1D(int);
    void showSpectrumAs1D(std::vector<int> indices);
    void showSpectrumMetaData(int);
private:
    QLineEdit* spectra_search_box_ = nullptr;
    QComboBox* spectra_combo_box_ = nullptr;
    QTreeWidget* spectra_treewidget_ = nullptr;
    /// cache to store mapping of chromatogram precursors to chromatogram indices
    std::map<size_t, std::map<Precursor, std::vector<Size>, Precursor::MZLess> > map_precursor_to_chrom_idx_cache_;
    /// remember the last PeakMap that we used to fill the spectra list (and avoid rebuilding it)
    const PeakMap* last_peakmap_ = nullptr;

private slots:
   /// fill the search-combo-box with current column header names
    void populateSearchBox_();
    /// searches for rows containing a search text (from spectra_search_box_); called when text search box is used
    void spectrumSearchText_();
    /// allows to show/hide columns
    void spectrumBrowserHeaderContextMenu_(const QPoint &);
    void spectrumSelectionChange_(QTreeWidgetItem *, QTreeWidgetItem *);
    void searchAndShow_(); ///< searches using text box and plots the spectrum
    void spectrumDoubleClicked_(QTreeWidgetItem *); ///< called upon double click; emits spectrumDoubleClicked() after some checking (opens a new Tab)
    void spectrumContextMenu_(const QPoint &);
  };
}
